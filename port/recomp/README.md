# SSX 3 on the PS2Recomp runtime

This builds SSX 3 for 32-bit Linux by translating the retail `SLUS_207.72` to C++ with
[PS2Recomp](https://github.com/ran-j/PS2Recomp) and linking it against PS2Recomp's runtime, with our fixes
applied. The translated code is generated in the build directory and is never committed. Neither is the ELF
or any disc file.

## What's here

- `CMakeLists.txt` fetches PS2Recomp at a fixed commit, applies `ps2recomp.patch`, finds function boundaries
  with spimdisasm, translates the ELF, then builds the runtime 32-bit.
- `ps2recomp.patch` holds our runtime changes. None of them are SSX 3 specific, so they could go upstream:
  - a 32-bit build, with EE RAM identity-mapped at its PS2 addresses;
  - EE→IOP SIF commands;
  - `sceCdCallback`;
  - semaphores with a max count of 0;
  - callback stacks kept clear of the main thread's stack;
  - GS CSR FIFO status;
  - a resident-module list for `sceSifSearchModuleByName`;
  - MPEG movies that pull their data through the game's Nodata callback, and end when the stream does;
  - a way for a game to move the runtime's scratch allocations out of its own heap;
  - the debug panel hidden until F1 is pressed (or `PS2X_DEBUG_UI=1`);
  - VIF `UNPACK V4-5` expanding 5:5:5:1 colours to 8 bits per channel, as the hardware does;
  - a guest call that yields before its callee starts no longer counts as finished when the callee is the
    function the call came from (EA's file system recurses this way while a race loads);
  - `BLTZ`/`BGEZ`/`BLEZ`/`BGTZ` (and their likely/link forms) testing the whole 64-bit register, like `SLT` and
    `BEQ` already do; EA's file table compares hashes with `LWU`+`DSUBU`+`BLTZ`, and a 32-bit test sorted it
    wrongly, so some riders' texture archives were never found;
  - `SQRT.S` taking its operand from the `ft` field, where the R5900 encodes it (the translator read `fs`,
    which is always `$f0`); SSX 3's lighting normalises light directions with it, and without the fix the
    riders' vertex colours saturated into rainbow noise;
  - VU0 macro-mode `VSQI`/`VLQI`/`VSQD`/`VLQD` and `VILWR`/`VISWR` addressing VU0 data memory rather than the
    bottom of EE RAM, with `VSQI`/`VSQD` storing `fs` at `it` (the translator had the two fields swapped). SSX 3
    stores matrices this way for a VU0 microprogram that decides which world objects are in view, so most close
    scenery was dropped;
  - `VCALLMSR` starting the microprogram at `CMSAR0` (it read past the 16 VI registers, so it jumped anywhere);
  - `CVT.W.S` truncating toward zero and saturating, as the R5900 always does (it rounded to nearest);
  - VU0 macro `DIV`/`SQRT`/`RSQRT` and `FTOI` giving the hardware results for zero divisors, negative inputs,
    `RSQRT`'s numerator and positive overflow;
  - `MSKPATH3` holding PATH3 back one GIF packet at a time, as the hardware does: clearing the mask lets the next
    queued packet through, and setting it again stops PATH3 once that packet ends (the runtime used to send
    everything queued). SSX 3 streams its textures this way, one per unmask, between the draws that use them.
    Sending them all at once left most of a frame drawn with whichever texture went up last, and ran the
    end-of-frame depth effect's `TEXA` setting before the 3D, which turned the snow under the riders' shadows black;
  - DMA chains longer than 4,096 tags being sent whole. The cut-off dropped the end of SSX 3's race list, which
    draws the player's rider and the stadium at the start gate;
  - a faster VU1 interpreter with the same results: it checks its pipelines only when a queued result is due,
    works out FMAC flags in `double` (exact for VU products and sums) and only falls back to `long double` at the
    edge of the float range, and copies `XGKICK` packets 16 bytes at a time. Replaying 4,000 VU1 microprogram runs
    recorded in an SSX 3 race gives bit-identical output, about 2.5 times faster;
  - the IOP catching up 256 cycles (2,048 EE cycles) at a time instead of after every block of EE code. Each catch-up
    walks the IOP's threads, timers and interrupts, and doing that every few EE instructions cost SSX 3 about a fifth
    of its main thread;
  - the GS rasterizer running a triangle pixel's depth test before its colour and texture work, since a pixel that
    fails it is dropped anyway, and rounding filtered texels without a libm call. 8,000 GS packets recorded in a race
    replay to the same VRAM about 10% faster;
  - GS drawing on worker threads. The runner queues draws, uploads and VRAM writes, and every worker runs them in
    order, each in the rounding mode its caller had, drawing only its own bands of 16 rows. Uploads, VRAM writes, and
    draws that read what another worker may still be drawing (render to texture, effects that read their own
    framebuffer) wait for every worker at that point and run on one. Anything that reads VRAM back waits for the queue
    first, so what the game sees is unchanged, and the window shows a frame once everything drawn before it is done,
    without waiting on the GS. One worker gave 1.6 to 2.2 times the frames of drawing on the game thread, and on a
    4-core machine two workers gave 1.57 times the frames of one;
  - debug switches.
- `ssx3_overrides.cpp` holds the game-specific replacements: it skips the network and USB keyboard drivers,
  answers the module search, routes `isceSifSendCmd`, and keeps the runtime's scratch buffers in the
  0x80000-0x100000 gap below the ELF, since the game's own allocator owns everything above it.
- `ssx3.toml.in` is the translator config (the analyzer's stub and entry lists). `gen_funcs.py` and
  `function_splits.txt` produce its function map.

## Building

You need a 32-bit toolchain and X/GL libraries, plus the decomp's Python venv, which provides spimdisasm.
On Debian/Ubuntu:

```bash
sudo dpkg --add-architecture i386 && sudo apt update
sudo apt install g++-multilib cmake ninja-build libgl-dev:i386 libx11-dev:i386 libxrandr-dev:i386 \
    libxinerama-dev:i386 libxcursor-dev:i386 libxi-dev:i386 \
    libavcodec-dev:i386 libavformat-dev:i386 libavutil-dev:i386 libswresample-dev:i386 libswscale-dev:i386
cmake -S port/recomp -B port/recomp/build -G Ninja -DSSX3PC_ELF=/path/to/SLUS_207.72 -DSSX3PC_RUNTIME_JOBS=4
ninja -C port/recomp/build
```

The translator turns about 14,700 functions into the same number of C++ files, so the runtime build is long.
Each compile job needs up to about 3 GB of memory, and that's what `SSX3PC_RUNTIME_JOBS` is for.

FFmpeg plays the game's movies. Pass `-DSSX3PC_FFMPEG=OFF` to build without it (the game then waits forever on
the first movie), or `-DSSX3PC_PKG_CONFIG_PATH=...` if your 32-bit FFmpeg lives elsewhere.

The runtime's per-function trace log (`ps2_log.txt`, written next to the ELF) and its IOP RPC trace are off by default:
the trace flushes every guest function call to disk and slows races from about 2.3 to 1.6 frames a second.
Pass `-DSSX3PC_TRACE_LOGS=ON` to turn them back on.

The runtime is built with `-mfpmath=sse`. Without it a 32-bit build does float maths on the x87 unit, which
turns PS2 floats with the top exponent (ordinary large numbers on the PS2) into NaNs.

### PS2Recomp's tests

PS2Recomp's test runner links the runtime, so it needs the same 32-bit flags. Once the build above has fetched
and patched PS2Recomp into `port/recomp/build/ps2recomp`:

```bash
PKG_CONFIG_PATH=/usr/lib/i386-linux-gnu/pkgconfig cmake -S port/recomp/build/ps2recomp -B /tmp/ps2x-tests -G Ninja \
    -DCMAKE_BUILD_TYPE=Release "-DCMAKE_C_FLAGS=-m32 -msse4.2 -mfpmath=sse" \
    "-DCMAKE_CXX_FLAGS=-m32 -msse4.2 -mfpmath=sse" -DCMAKE_EXE_LINKER_FLAGS=-m32 -DPS2X_BUILD_STUDIO=OFF
ninja -C /tmp/ps2x-tests ps2x_tests
cd port/recomp/build/ps2recomp && /tmp/ps2x-tests/ps2xTest/ps2x_tests
```

Run it from the PS2Recomp source folder: one test reads `instructions.h` by relative path.

## Running

Run it from a folder holding the extracted disc, and point `PS2X_CD_IMAGE` at an ISO of the disc:

```bash
cd /path/to/extracted-disc
PS2X_CD_IMAGE=/path/to/ssx3.iso /path/to/port/recomp/build/runtime/ps2xRuntime/ps2EntryRunner "$PWD/SLUS_207.72"
```

These debug switches print to stderr:

| Variable | Prints |
| --- | --- |
| `PS2X_DUMP_THREADS=1` | the EE thread table every 5 s, with return addresses from each stack |
| `PS2X_SIF_LOG=1` | SIF commands in both directions |
| `PS2X_CD_LOG=1` | CD reads and `sceCdCallback` calls |
| `PS2X_FILE_LOG=1` | the game's file lookups and their results, each file command it queues, and each one that fails |
| `PS2X_MPEG_LOG=1` | MPEG callbacks, data fed to the decoder, and the end of each movie |
| `PS2X_HEAP_LOG=1` | the runtime's scratch allocations |
| `PS2X_DUMP_RDRAM=file` with `PS2X_DUMP_RDRAM_TICK=n` | EE RAM, written to `file` at frame `n` |
| `PS2X_DUMP_RDRAM_ON_FAULT=file` | EE RAM, written to `file` the first time guest code jumps to an unknown address |
| `PS2X_VU1_LOG=1` | how often each VU1 microprogram runs, and VIF1 codes the interpreter skips |
| `PS2X_FRAME_LOG=1` | how many passes of the game's main loop run per second, every 2 s |
| `PS2X_GS_SAMPLE=flagfile` | once `flagfile` exists, 3000 non-sprite primitives drawn to the main framebuffer |

`PS2X_GS_THREADS=n` draws with `n` GS worker threads, and 0 draws on the game thread. By default it uses the cores
the game and window threads leave free, up to 6.

Keyboard: Enter is START, X is Cross, Z is Square; F1 shows the debug panel.

## Status

With the full disc, the game plays the EA SPORTS BIG logo movie, shows the title screen, and takes keyboard
input through the front end to a race. In the race, the HUD, sky, mountains, start-gate stadium, riders, their
shadows and the course draw with the right textures, and the race plays from the gate down the first slope.
The camera sits much further behind the player's rider than it should. Sound has not been tested yet.

It is far from full speed. On a 4-core 2.1 GHz Xeon, a race draws about 4 to 6.5 frames a second.

When a guest address with no function is reached, the scheduler prints its last 64 dispatches (`[sched-trace]`).
