// SPDX-License-Identifier: GPL-3.0-or-later
// Calls a natively compiled game function with the arguments an EE caller left
// in its registers. Included at the end of each generated unit wrapper, so it
// sees the function's real type; it uses no runtime headers, since game code
// declares its own C library functions.
//
// The EE EABI passes int and pointer arguments in a0-a3, t0-t3 and float
// arguments in f12-f19, each kind counted on its own, and returns them in v0 or
// f0. A 32-bit value always sits sign-extended in a 64-bit register; the
// runtime side does that when it copies the result back.
#ifndef SSX3_NATIVE_ABI_H
#define SSX3_NATIVE_ABI_H

#include <type_traits>
#include <utility>

struct Ssx3NativeFrame
{
    unsigned int gpr[8]; // a0-a3, t0-t3 (low 32 bits)
    float fpr[8];        // f12-f19
    unsigned int v0;
    float f0;
    unsigned int result; // 0 none, 1 v0, 2 f0
};

namespace ssx3native
{
    template <typename T>
    constexpr bool isFloat = std::is_same<typename std::remove_cv<T>::type, float>::value;

    template <typename T>
    constexpr bool wordKind()
    {
        if constexpr (std::is_integral<T>::value || std::is_enum<T>::value || std::is_pointer<T>::value)
            return sizeof(T) <= 4 && !std::is_same<typename std::remove_cv<T>::type, bool>::value;
        else
            return false;
    }

    template <typename T>
    constexpr bool isWord = wordKind<T>();

    // Register slot of argument I: how many earlier arguments are of the same kind.
    template <typename... A>
    constexpr int slot(int i)
    {
        constexpr bool floats[] = {isFloat<A>..., false};
        int n = 0;
        for (int k = 0; k < i; ++k)
            n += floats[k] == floats[i];
        return n;
    }

    template <typename T, int Slot>
    T arg(const Ssx3NativeFrame *f)
    {
        if constexpr (isFloat<T>)
            return f->fpr[Slot];
        else if constexpr (std::is_pointer<T>::value)
            return reinterpret_cast<T>(static_cast<unsigned long>(f->gpr[Slot]));
        else
            return static_cast<T>(f->gpr[Slot]);
    }

    template <typename Sig>
    struct Thunk;

    template <typename R, typename... A>
    struct Thunk<R(A...)>
    {
        static_assert(((isFloat<A> || isWord<A>) && ...), "argument kind the EE passes some other way");
        static_assert(std::is_void<R>::value || isFloat<R> || isWord<R>, "result kind the EE returns some other way");

        template <R (*F)(A...), std::size_t... I>
        static void call(Ssx3NativeFrame *f, std::index_sequence<I...>)
        {
            static_assert(((slot<A...>(I) < 8) && ...), "more than 8 register arguments of one kind");
            f->result = std::is_void<R>::value ? 0u : isFloat<R> ? 2u : 1u;
            if constexpr (std::is_void<R>::value)
                F(arg<A, slot<A...>(I)>(f)...);
            else if constexpr (isFloat<R>)
                f->f0 = F(arg<A, slot<A...>(I)>(f)...);
            else if constexpr (std::is_pointer<R>::value)
                f->v0 = static_cast<unsigned int>(reinterpret_cast<unsigned long>(F(arg<A, slot<A...>(I)>(f)...)));
            else
                f->v0 = static_cast<unsigned int>(static_cast<int>(F(arg<A, slot<A...>(I)>(f)...)));
        }

        template <R (*F)(A...)>
        static void call(Ssx3NativeFrame *f)
        {
            call<F>(f, std::index_sequence_for<A...>{});
        }
    };
} // namespace ssx3native

// One entry point per swapped function, named for its EE address.
#define SSX3_NATIVE(ADDR, NAME)                                                         \
    extern "C" void ssx3n_##ADDR(Ssx3NativeFrame *f)                                     \
    {                                                                                   \
        ssx3native::Thunk<typename std::remove_pointer<decltype(&NAME)>::type>::template \
            call<&NAME>(f);                                                             \
    }

#endif
