// SPDX-License-Identifier: GPL-3.0-or-later
// Runs game functions compiled from the decompiled C in place of their
// recompiled copies. native/gen_native.py builds them and their table; this
// file swaps them in.
//
// Each swapped function takes its arguments from the EE registers and returns
// through v0 or f0, as the EE caller expects. Native code works on EE memory
// directly: EE RAM is mapped at its PS2 addresses in the 32-bit process.
//
// PS2X_NATIVE=0 keeps every function recompiled. PS2X_NATIVE_CHECK=n runs the
// first n calls of each swapped function both ways from the same RAM and
// registers and reports any difference in EE RAM or in the result (debug only:
// it copies all of EE RAM three times per checked call).
//
// Recompiled code wraps every address into EE RAM, so a stray pointer the game
// follows (it does: a UI animation is updated after its track array is freed and
// reused) still reads RAM. Native code faults instead; the SIGSEGV handler then
// maps the RAM page that address wraps to at that address and retries, so both
// read the same.
#include "native/native_abi.h"
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"

#ifdef _WIN32
// A Windows build doesn't map EE RAM at its PS2 addresses (SSX3PC_NATIVE is off
// there), so every function stays recompiled.
void ssx3RegisterNative(PS2Runtime &)
{
}
#else

#include <atomic>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <sys/mman.h>
#include <unordered_map>

struct Ssx3NativeEntry
{
    unsigned int address;
    void (*entry)(Ssx3NativeFrame *);
};
// Weak, so the runner still links when built with SSX3PC_NATIVE=OFF.
extern "C" const Ssx3NativeEntry g_ssx3NativeTable[] __attribute__((weak));
extern "C" const unsigned int g_ssx3NativeCount __attribute__((weak));

// Native code reached a function that stays recompiled. The picker only swaps
// functions whose callees are swapped too, so this means the lists are stale.
extern "C" void ssx3NativeUnreachable(const char *name)
{
    std::fprintf(stderr, "[native] called %s, which is not native; regenerate native_functions.txt\n", name);
    std::abort();
}

namespace
{
    struct Swapped
    {
        void (*entry)(Ssx3NativeFrame *);
        PS2Runtime::RecompiledFunction recompiled;
        uint32_t checksLeft;
        uint32_t mismatches;
    };

    std::unordered_map<uint32_t, Swapped> g_swapped;
    uint32_t g_checkCalls = 0;
    uint32_t g_checksPerFunction = 0;
    bool g_inCheck = false;

    // Set while this thread runs native code; only its faults are wrapped.
    thread_local int t_inNative = 0;
    uint8_t *g_rdram = nullptr;
    std::atomic<uint32_t> g_wrappedPages{0};
    struct sigaction g_prevSegv;

    void onSegv(int sig, siginfo_t *info, void *uc)
    {
        const uintptr_t addr = reinterpret_cast<uintptr_t>(info->si_addr);
        if (t_inNative > 0 && info->si_code == SEGV_MAPERR && addr >= 0x10000u && g_rdram)
        {
            // An unmapped page: show the RAM page the recompiled code would read there.
            const uintptr_t page = addr & ~uintptr_t(0xFFF);
            void *view = mremap(g_rdram + (page & PS2_RAM_MASK), 0, 0x1000, MREMAP_MAYMOVE | MREMAP_FIXED,
                                reinterpret_cast<void *>(page));
            if (view == reinterpret_cast<void *>(page))
            {
                g_wrappedPages.fetch_add(1u, std::memory_order_relaxed);
                return;
            }
        }
        if (g_prevSegv.sa_flags & SA_SIGINFO)
            g_prevSegv.sa_sigaction(sig, info, uc);
        else if (g_prevSegv.sa_handler != SIG_DFL && g_prevSegv.sa_handler != SIG_IGN)
            g_prevSegv.sa_handler(sig);
        else
        {
            std::signal(sig, SIG_DFL);
            std::raise(sig);
        }
    }

    void installSegvHandler()
    {
        struct sigaction sa{};
        sa.sa_sigaction = onSegv;
        sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
        sigemptyset(&sa.sa_mask);
        sigaction(SIGSEGV, &sa, &g_prevSegv);
    }

    // Returns what the function gives back: 0 nothing, 1 v0, 2 f0.
    unsigned int runNative(const Swapped &fn, R5900Context *ctx)
    {
        Ssx3NativeFrame frame{};
        for (int i = 0; i < 8; ++i)
        {
            frame.gpr[i] = getRegU32(ctx, 4 + i);
            frame.fpr[i] = ctx->f[12 + i];
        }
        ++t_inNative;
        fn.entry(&frame);
        --t_inNative;
        if (frame.result == 1u)
            SET_GPR_S32(ctx, 2, static_cast<int32_t>(frame.v0));
        else if (frame.result == 2u)
            ctx->f[0] = frame.f0;
        ctx->pc = getRegU32(ctx, 31);
        return frame.result;
    }

    // Runs the recompiled copy, then the native one from the same state, and
    // compares. Returns false (state untouched) when the recompiled copy did not
    // run to its return, e.g. it stopped at a scheduler checkpoint.
    bool checkCall(uint32_t address, Swapped &fn, uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        static std::unique_ptr<uint8_t[]> before(new uint8_t[PS2_RAM_SIZE]);
        static std::unique_ptr<uint8_t[]> expected(new uint8_t[PS2_RAM_SIZE]);
        auto saved = std::make_unique<R5900Context>(*ctx);
        const uint32_t ra = getRegU32(ctx, 31);
        const uint32_t sp = getRegU32(ctx, 29) & PS2_RAM_MASK;

        std::memcpy(before.get(), rdram, PS2_RAM_SIZE);
        g_inCheck = true;
        fn.recompiled(rdram, ctx, runtime);
        g_inCheck = false;
        if (ctx->pc != ra)
        {
            std::memcpy(rdram, before.get(), PS2_RAM_SIZE);
            *ctx = *saved;
            return false;
        }
        const uint32_t v0 = getRegU32(ctx, 2);
        const float f0 = ctx->f[0];
        std::memcpy(expected.get(), rdram, PS2_RAM_SIZE);
        std::memcpy(rdram, before.get(), PS2_RAM_SIZE);
        *ctx = *saved;

        const unsigned int result = runNative(fn, ctx);
        ++g_checkCalls;

        // The recompiled copy keeps its frame below sp; the native one uses the host stack.
        const uint32_t stackLo = sp > 0x10000u ? sp - 0x10000u : 0u;
        int reported = 0;
        uint32_t differing = 0;
        for (uint32_t a = 0; a < PS2_RAM_SIZE; a += 4)
        {
            if (a >= stackLo && a < sp)
                continue;
            if (std::memcmp(rdram + a, expected.get() + a, 4) == 0)
                continue;
            ++differing;
            if (reported < 4)
            {
                uint32_t want, got;
                std::memcpy(&want, expected.get() + a, 4);
                std::memcpy(&got, rdram + a, 4);
                std::fprintf(stderr, "[native] %08X: RAM %08X is %08X, recompiled wrote %08X\n", address, a, got, want);
                ++reported;
            }
        }
        const uint32_t nv0 = getRegU32(ctx, 2);
        const float nf0 = ctx->f[0];
        const bool resultDiffers = (result == 1u && nv0 != v0) || (result == 2u && std::memcmp(&nf0, &f0, 4) != 0);
        if (resultDiffers)
            std::fprintf(stderr, "[native] %08X: result v0=%08X f0=%g, recompiled v0=%08X f0=%g\n", address, nv0, nf0,
                         v0, f0);
        if (differing || resultDiffers)
        {
            ++fn.mismatches;
            std::fprintf(stderr, "[native] %08X: MISMATCH (%u words differ)\n", address, differing);
        }
        if ((g_checkCalls & 63u) == 0u)
        {
            uint32_t functions = 0, mismatched = 0;
            for (const auto &kv : g_swapped)
            {
                functions += kv.second.checksLeft != g_checksPerFunction;
                mismatched += kv.second.mismatches != 0u;
            }
            std::fprintf(stderr, "[native] checked %u calls of %u functions, %u functions differ, %u stray pages\n",
                         g_checkCalls, functions, mismatched, g_wrappedPages.load());
        }
        return true;
    }

    void nativeShim(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        g_rdram = rdram;
        const auto it = g_swapped.find(ctx->pc);
        if (it == g_swapped.end())
        {
            std::fprintf(stderr, "[native] entered at %08X, which is not a swapped function's start\n", ctx->pc);
            std::abort();
        }
        Swapped &fn = it->second;
        if (fn.checksLeft != 0u && !g_inCheck)
        {
            if (checkCall(it->first, fn, rdram, ctx, runtime))
                --fn.checksLeft;
            else
                runNative(fn, ctx);
            return;
        }
        runNative(fn, ctx);
    }
}

// PS2X_NATIVE_SKIP=addr,addr,... keeps those functions recompiled (to narrow down a problem).
static bool skipped(uint32_t address)
{
    static const char *list = std::getenv("PS2X_NATIVE_SKIP");
    for (const char *p = list; p && *p;)
    {
        char *end = nullptr;
        const unsigned long a = std::strtoul(p, &end, 16);
        if (end == p)
            break;
        if (a == address)
            return true;
        p = *end == ',' ? end + 1 : end;
    }
    return false;
}

void ssx3RegisterNative(PS2Runtime &runtime)
{
    if (&g_ssx3NativeCount == nullptr)
        return;
    const char *off = std::getenv("PS2X_NATIVE");
    if (off && std::strcmp(off, "0") == 0)
    {
        std::fprintf(stderr, "[native] off: all game code recompiled\n");
        return;
    }
    const char *check = std::getenv("PS2X_NATIVE_CHECK");
    const uint32_t checks = check ? static_cast<uint32_t>(std::strtoul(check, nullptr, 0)) : 0u;
    g_checksPerFunction = checks;
    installSegvHandler();
    uint32_t swapped = 0;
    for (unsigned int i = 0; i < g_ssx3NativeCount; ++i)
    {
        const Ssx3NativeEntry &e = g_ssx3NativeTable[i];
        PS2Runtime::RecompiledFunction recompiled = runtime.lookupFunction(e.address);
        if (!recompiled)
            continue; // the translator found no function starting here
        if (skipped(e.address))
            continue;
        g_swapped[e.address] = {e.entry, recompiled, checks, 0u};
        runtime.replaceFunction(e.address, nativeShim);
        ++swapped;
    }
    std::fprintf(stderr, "[native] %u of %u decompiled functions run as native code%s\n", swapped,
                 g_ssx3NativeCount, checks ? " (checking them against the recompiled copies)" : "");
}
#endif
