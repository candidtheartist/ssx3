# SSX 3 on the PS2Recomp runtime

This builds SSX 3 for 32-bit Linux and Windows by translating the retail `SLUS_207.72` to C++ with
[PS2Recomp](https://github.com/ran-j/PS2Recomp) and linking it against PS2Recomp's runtime, with our fixes
applied. The translated code is generated in the build directory and is never committed. Neither is the ELF
or any disc file.

## What's here

- `CMakeLists.txt` fetches PS2Recomp at a fixed commit, applies `ps2recomp.patch`, finds function boundaries
  with spimdisasm, translates the ELF, then builds the runtime 32-bit.
- `apply_patch.cmake` applies the patch. When a pull changes the patch, the next build rewrites only the files
  it changes, so only what depends on them recompiles.
- `ps2recomp.patch` holds our runtime changes. None of them are SSX 3 specific, so they could go upstream:
  - a 32-bit build, with EE RAM identity-mapped at its PS2 addresses;
  - a native 32-bit Windows build with MinGW. The game thread gets a 16 MB stack, and `operator new` returns
    16-byte aligned memory, which GCC assumes but 32-bit MinGW's `malloc` does not give. EE RAM is not mapped at
    its PS2 addresses there, since Windows 11 already has memory at 0x00100000 when a process starts; the
    recompiled code doesn't need it, only natively compiled C does, so a Windows build keeps every function
    recompiled (`SSX3PC_NATIVE` is off there);
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
    order, each in the rounding mode its caller had, drawing only its own bands of rows. Uploads, VRAM writes, and
    draws that read what another worker may still be drawing (render to texture, effects that read their own
    framebuffer) wait for every worker at that point and run on one. Anything that reads VRAM back waits for the queue
    first, so what the game sees is unchanged, and the window shows a frame once everything drawn before it is done,
    without waiting on the GS. One worker gave 1.6 to 2.2 times the frames of drawing on the game thread, and on a
    4-core machine two workers gave 1.57 times the frames of one;
  - the GS workers also sharing two kinds of draw that read the buffer they draw to: a sprite that copies a buffer onto
    itself pixel for pixel, since each pixel then reads only itself, and a UV sprite whose texels are worked out
    exactly, with the sprite rasterizer's own maths, so a resample from one buffer into the next no longer looks like
    it reads what it draws. These were SSX 3's three full-screen effect passes, the last draws that ran on one worker.
    The recorded race packets replay to the same VRAM about 15% faster with three workers;
  - a faster IOP interpreter: IOP RAM reads and writes are inline, an instruction is checked for an import stub only
    when it is a `jr $ra`, and the next DMA completion is kept at hand instead of being looked for after every
    instruction. SSX 3 mixes its sound on the IOP, and in a race each IOP instruction took about 24 ns instead of 38 to
    47;
  - the VU1 interpreter working out an FMAC instruction's result and its flags in one pass, over only the fields it
    writes. The 4,000 recorded VU1 runs still give bit-identical output, with about 5% fewer instructions. With the
    GS and IOP changes, a race draws about 8% more frames;
  - every new thread, interrupt handler and callback starting with VU0's `vf0` as (0, 0, 0, 1), as the hardware always
    reads it. The runtime started them with it cleared, and it was only set again once a VU0 microprogram ran. SSX 3
    builds the player's rider on a newly started loader thread, turning each bone's rest pose from a quaternion with
    code that reads `vf0`, so the bones' rest-pose matrices came out as zeros and the player's rider drew tiny, with
    stretched legs, in front of the camera;
  - SPU2 AutoDMA transfers finishing once the SPU2 would have played them, one stereo frame per 48 kHz sample, and
    their sound playing through the PC's audio device. SSX 3's sound driver mixes everything on the IOP and streams
    the mix to core 0 in blocks of 512 frames. The runtime dropped the data and finished each block about 400 times
    too soon, so the driver kept resending stale blocks. Paced, a race draws about 4% more frames;
  - a VU1 interpreter that does about half the work for the same results. The add, subtract, multiply and
    multiply-add instructions run on all four fields at once with SSE4.1, with a short path for their flags when
    every result is an ordinary float. Each instruction pair's register waits are worked out once, when the code is
    decoded. Queued flags, stores and integer writes land through a wheel of per-cycle slots instead of being
    searched for every cycle, and vector and `ACC` results go into the registers when they issue, since every read
    of a field already waits until its result is due. The 4,000 recorded VU1 runs still give bit-identical output,
    with 46% fewer instructions. In a race on a 4-core machine the game thread went from busy nearly all the time
    to about two thirds of it, and now waits on the two GS workers;
  - the GS rasterizer settling a draw's texture and pixel setup once per primitive instead of for every pixel: the
    wrap modes, texel format, frame and depth formats and blend inputs are worked out before the pixel loop, filtered
    texels are blended four channels at a time with SSE2, and each palette entry is converted once per CLUT load
    rather than for every texel. A primitive whose texture shares no VRAM page with the buffers it draws to reads its
    texels straight from VRAM instead of copying each 8 KiB page first. The 8,000 recorded race packets replay to the
    same VRAM, also with round-toward-zero and on several workers, with 22% fewer instructions. A race on a 4-core
    machine went from about 8 to about 10 frames a second;
  - the GS workers drawing bands of 4 rows instead of 16, and waiting for each other once per texture rather than
    once per mip level: a texture's transfers, texture flushes and CLUT load now run together while the workers
    wait. With 16-row bands a small object's rows fell to only a few workers. Replaying the recorded race packets on
    8 workers, the busiest drew 42% more pixels between waits than the average, and 6% more with 4-row bands, for
    the same total work. On a 4-core machine's two workers neither change moved the frame rate;
  - a second round on the VU1 interpreter, again with the same results. `MAX`, `MINI`, `ITOF`, `FTOI`, `ABS`,
    `OPMULA` and `OPMSUB` now run on all four fields at once too, and upper `NOP`s are skipped. `ACC` is ready for
    the very next instruction, so the bookkeeping of when its fields land never changed anything and is gone. Flag
    results land in the order they issued, each as bits to keep and bits to set, and an integer register
    write due by the next cycle goes straight into the register. The 4,000 recorded VU1 runs still give
    bit-identical output, with 18% fewer instructions, and replay 1.4 times as fast in the 32-bit build; 400,000
    random microprograms end in the same state as before the change. In a race on a 4-core machine the GS workers
    still set the pace: about 9 frames a second against 8.5 before, within this machine's run-to-run noise;
  - compiled blocks for VU1 programs, again with the same results. A VU1 instruction's stall depends only on how
    many cycles each queued result still needs, never on a value, so a straight run of instruction pairs is
    compiled once for each start address and pipeline timing it is entered with, with every stall known ahead.
    Blocks skip the interpreter's hazard checks and per-cycle commits and run the common pairs through decoded
    paths; stores land as they issue, and flag results stay queued until something reads them. Anything a block
    can't run (D or T bits, a reserved op, the end of the cycle budget, a GS packet error) hands over to the
    interpreter at that pair with the pipeline timing rebuilt. Blocks are kept for up to 8 code images, found by
    content, since the game uploads the same microcode again and again. The 4,000 recorded VU1 runs still give
    bit-identical output with 53% fewer instructions, and replay 2.3 times as fast in the 32-bit build. A test runs
    3,000 random microprograms both ways. In a race on a 4-core machine the game thread is busy about a third
    less for the same frame rate, which the GS workers still set. `PS2X_VU1_COMPILED=0` turns them off;
  - the GS rasterizer's pixel code specialised by format, again with the same results. Each texture format's
    swizzle is read inline instead of through one shared function. The common frame and depth buffer pairs get their
    own copy of the sprite and triangle loops, which reads and writes a pixel at one worked-out address instead of
    calling through a table for every access. A triangle tests only the pixels of each row that can pass its edge
    tests, instead of its whole bounding box, which in a race holds 4.5 times as many pixels as pass. That range is
    solved in double precision with room for the float rounding, so every pixel it leaves out fails the float tests
    too; 900,000 random triangles checked it against the full test in both rounding modes. The 8,000 recorded race packets replay to the same
    VRAM, also with round-toward-zero and on several workers, with 25% fewer instructions. In a race on a 4-core
    machine with the old and new code swapped every 30 s, the new code drew about 30% more frames;
  - the GS rasterizer's texture reads and pixel arithmetic trimmed, again with the same results. The four reads of a
    filtered texel nearly always lie in one VRAM page, so they look that page up in the texture page cache once.
    Alpha blending, and a triangle pixel's colour, S, T, Q and fog sums, run one channel per SIMD lane with the same
    operations in the same order. The per-pixel scissor test is skipped where the loop already keeps to the scissor
    rectangle. The 8,000 recorded race packets replay to the same VRAM with 16% fewer instructions. In a race on a
    4-core machine with the old and new code swapped every 30 s, the new code drew about 8% more frames;
  - the GS pixel loops working from their own copies of the draw state and vertices they read for every pixel. Writes
    to VRAM go through byte pointers, so before this the compiler had to read that state again after each pixel
    write. A filtered sample that reads the same four texels as the one before reuses their colours, as long as the
    texture page cache has not loaded another page since. The 8,000 recorded race packets replay to the same VRAM
    with 12% fewer instructions. In a race with the old and new code swapped every 30 s, the new code drew about 4%
    more frames, which is within this machine's run-to-run noise;
  - VIF1, VU1 and the GIF running on a thread of their own, so the game thread runs only the EE. VIF1 and GIF DMA,
    VIF1 FIFO writes and stores to the GS privileged registers other than CSR become jobs that run there in order.
    The DMA still reports done at once, and the job reads a copy of the memory it was started on. The EE waits for
    the thread before it reads or changes anything a job uses (VU1 memory, the VIF1 registers, those GS registers),
    and stays at most 3 vertical blanks ahead of the drawing. VU1 programs that stop on a D or T bit for the EE
    to see still run on the game thread. In a race on a 4-core machine with the thread switched on and off every
    30 s, the game thread was busy 24% of the time instead of 53%. The frame rate stayed within this machine's
    run-to-run noise (13.5 against 12.6 a second), since the GS workers still set it; with drawing skipped, the
    race ran 31% faster;
  - the GS pixel loops specialised further, with the same results. A pixel works out its depth buffer address once
    for the depth test and the write. Texture reads are compiled for the texture format as well as the frame and
    depth formats in the pairs a race uses (CT32 frames with CT32, CT16, T8, T4 and T8H textures, CT24 frames with
    CT32). MODULATE and DECAL texture combining run on all four channels at once and hand the packed colour
    straight to the pixel write. The texture page cache copies a page only when it is about to be written, the 16
    or 256 entry palette is filled when it is loaded instead of checked for every texel, and a sprite whose
    filtered samples land on texel centres reads one texel instead of four. The 8,000 recorded race packets replay
    to the same VRAM, also with round-toward-zero and on several workers, with 24% fewer instructions. In a race
    on a 4-core machine with the old and new code swapped every 30 s, the new code drew about 16% more frames
    (15.7 against 13.5 a second);
  - the GS workers waiting on each other less, with the same results. With more than one worker, each worker reads
    textures and CLUTs from its own copy of VRAM and applies the EE's uploads to it in command order, so an upload
    into a texture slot that slower workers are still reading from no longer stops every worker, the most common
    wait in a race. Pages the workers drew are copied into each worker's copy just before a later draw reads them
    as a texture. Commands go through a ring that the workers take from with no sync at the end of each batch, and
    uploads write a row of pixels at a time. The 8,000 recorded race packets replay to the same VRAM, also with
    round-toward-zero and on several workers, with 4% fewer instructions and 63 syncs instead of 289. In a 20-minute
    race with the old and new code swapped every 30 s, the GS workers stopped to wait for each other 4.4 times less
    often and got through 5% more commands a second; the frame rate changed by less than this machine's run-to-run
    noise;
  - a sprite's texel reads worked out once per column and once per row instead of for every pixel: which texels
    it reads, wrapped as CLAMP sets up, and their filter weights. The full-screen passes are sprites, so the 8,000
    recorded race packets replay to the same VRAM, also with round-toward-zero and on several workers, with 5%
    fewer instructions;
  - `printf`, `sprintf` and `scePrintf` reading their arguments the way EE code passes them: every argument,
    32 or 64 bits, takes one 64-bit argument register and then one 8-byte stack slot. The runtime read them as
    32-bit slots, so a `double` (a soft float in one register) came out as 0. SSX 3 prints race and record times
    with `%02.0f`, and every time on the results and records screens read 00:00;
  - VU1 blocks run as C++ written for each block at build time, with the same results. The block executor steps
    through a list of decoded pairs; for each block in `vu1_blocks.txt`, the build instead writes one function in
    which every pair's decoded fields are constants, so the compiler specialises each pair's code. A block is found
    by its start address, the pipeline timing it is entered with and a hash of its own instructions, so it does not
    matter which upload or code image it came from. The list holds only numbers: the build reads the VU1 code from
    the VIF packets in the ELF's `.vutext` section, and the generated files stay in the build tree. Blocks not in
    the list run on the executor as before. The 4,000 recorded VU1 runs still give bit-identical output and replay
    1.45 times as fast as on the executor in the 32-bit build. A test generates blocks for 100 random microprograms
    and runs them against the interpreter. In a race every block the game ran had generated code, and VU1 programs
    took 29% less time per block (330 against 460 ns, not counting GS packet hand-off); the GS workers still set the
    frame rate. `PS2X_VU1_GENERATED=0` turns them off;
  - the GS renderer and VU1 built at -O3 in every optimised build type, with the same results. The runtime is built
    as RelWithDebInfo, and at its -O2 the compiler left some per-pixel helpers, such as the bilinear filter, as
    separate calls; these files now get -O3 whatever the build type, except Debug. A primitive also works out once
    what its alpha and destination alpha tests let a pixel write, and a sprite works out each column's part of its
    frame and depth addresses once. The 8,000 recorded race packets replay to the same VRAM, also with
    round-toward-zero and on several workers, in 10% less time on one worker and 26% less on three. The same race on
    the old and new build ran at a median 13.2 and 16.1 frames a second over its last 5 minutes, and its race clock
    moved 16% faster;
  - PS2 float results kept whole when a float helper returns them. The 32-bit x86 ABI returns a float on the x87
    stack, and loading it there turns an exponent-255 value with the top mantissa bit clear (an ordinary large
    number on the PS2) into a quiet NaN. The out-of-line helpers that handle such values now return the result's
    bits, and the inline ones are always inlined. One of the FPU hardware-results tests failed at the game's
    RelWithDebInfo build type before this, though it passed at Release;
  - the GS workers woken once per 32 queued commands instead of for each one, and skipping draws outside their
    rows, with the same results. A race start queues about 28,000 draws a frame. On an 8-core Windows PC, waking six
    workers for each one kept the thread that queues them signalling a fifth of the time, while the workers drew
    under a tenth of the time. Workers are still woken at once for a command they all wait at, and before anything
    waits for them. A worker also skips a draw that touches none of its rows, instead of setting it up to draw
    nothing. The recorded race packets replay to the same VRAM on 1, 2, 3 and 6 workers, also with
    round-toward-zero, with 7% fewer instructions on six workers. A race on a 4-core Linux machine woke the workers
    20 times less often, at the same frame rate. On the Windows PC the race clock went from 0.34 to 0.77 times
    real time;
  - the GS workers sleeping on a lock of their own, so a worker going idle or waking never waits for the thread
    that queues commands, which holds the queue's lock while it sorts out each one. On Windows a lock two threads
    want at once goes through the kernel, and that thread spent about 7% of its time releasing it;
  - the VU1 thread and the game thread that hands it VIF1 work waking each other only when the other is waiting.
    The VU1 thread signalled after every job it finished and the game thread after every job it queued, though
    each waits for the other only a few times a frame. On the Windows PC the VU1 thread spent about 7% of its
    time releasing those waits;
  - rounding-mode changes made with the x87 and SSE control registers directly. MinGW's 32-bit `fesetround`,
    `fegetenv` and `fesetenv` check for SSE with CPUID on every call, and CPUID traps into the hypervisor when
    Windows runs under one (as it does with memory integrity on). The VU1 thread switches to round-toward-zero
    around every VU1 program, the GS workers switch to each command's mode, and each VU1 thread job ran in a
    copy of the game thread's whole floating-point environment; a job now carries just its rounding mode;
  - Windows' own locks and condition variables (SRWLOCK, CONDITION_VARIABLE) for the VU1 thread and the GS
    workers, in place of MinGW's winpthreads ones, which sleep on a semaphore through WaitForMultipleObjects
    and wake through ReleaseSemaphore, a system call each time. On the Windows PC the six GS workers each spent
    about a fifth of a core in them. The workers also wait for each other at a barrier of their own, and
    a worker that waits there or runs out of commands checks again for a while before it sleeps
    (`PS2X_GS_SPIN` checks, 2000 by default), since the others or the next commands are usually microseconds
    away;
  - the same Windows waits for the EE scheduler, whose timed waits keep the game at 60 vblanks a second. With
    winpthreads they took 36 to 42% of the game thread on the Windows PC. Windows sleeps in whole
    milliseconds, so the last part of a millisecond before a deadline is waited out by yielding;
  - a fix for a picture that stopped changing while the game went on. A presentation request queued while the
    thread that queues draws was waiting for room in a full queue was overwritten by that thread's next draw, so
    the window kept its last frame for the rest of the session. A 4-core Linux machine, where the queue is often
    full, hit it in four runs out of seven, after 1 to 9 minutes; with the fix, the picture changed in every
    screenshot of a 10-minute run into a race;
  - a vertical blank that is due more than a frame ago timed from now. When frames take longer to run than to
    show, the host falls behind the PS2's schedule, and the game then ran fast until it had caught up: on the
    Windows PC a race's main loop went from about 50 passes a second to 166 for seconds at a time. Now a slow
    stretch just runs slowly;
  - debug switches.
- `ssx3_overrides.cpp` holds the game-specific replacements: it skips the network and USB keyboard drivers,
  answers the module search, routes `isceSifSendCmd`, and keeps the runtime's scratch buffers in the
  0x80000-0x100000 gap below the ELF, since the game's own allocator owns everything above it.
- `ssx3_native.cpp` and `native/` swap in game functions compiled from the decompiled C instead of
  their recompiled copies. Only functions that are certain to behave the same qualify; see
  [native/README.md](native/README.md). Linux only for now.
- `ssx3.toml.in` is the translator config (the analyzer's stub and entry lists). `gen_funcs.py` and
  `function_splits.txt` produce its function map. A stub runs the runtime's own version of a function instead of
  the game's, so a name goes on the list only when the runtime's version takes the same arguments: SSX 3's `log`
  (0x0040D610) takes and returns a soft `double` in integer registers, while the runtime's `log` stub works on a
  `float` in `$f12`, so `log` is translated from the game's code. The particle code that calls it got its own
  argument back instead of the logarithm.

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

### Windows

The Windows build uses the MINGW32 environment of [MSYS2](https://www.msys2.org), whose GCC builds 32-bit
programs, and a Windows Python for spimdisasm. Work in a folder whose path has no spaces. In a MINGW32 shell:

```bash
pacman -S --needed git make diffutils mingw-w64-i686-gcc mingw-w64-i686-cmake mingw-w64-i686-ninja mingw-w64-i686-pkgconf
git -c core.autocrlf=false clone https://github.com/candidtheartist/ssx3 && cd ssx3
py -3 -m venv venv && venv/Scripts/python.exe -m pip install "spimdisasm>=1.41.0"
cmake -S port/recomp -B port/recomp/build -G Ninja -DSSX3PC_ELF=C:/path/to/SLUS_207.72 -DSSX3PC_RUNTIME_JOBS=4
ninja -C port/recomp/build
```

The build also fetches FFmpeg and builds a small static copy of it with only the MPEG video decoder and the scaler,
so the game's movies play and `ps2EntryRunner.exe` needs no DLLs. Run it the same way as on Linux, from the
extracted disc's folder in the MINGW32 shell.

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
| `PS2X_GS_SPIN=n` | how many times a GS worker checks, with a pause, before it sleeps waiting for the others or for commands (2000) |
| `PS2X_FRAME_LOG=1` | every 2 s: passes of the game's main loop a second (two a vertical blank at full speed), the game's speed against a PS2 (1.00x is 60 vertical blanks a second) and the median, 95th-percentile and longest pass in ms |
| `PS2X_GS_SAMPLE=flagfile` | once `flagfile` exists, 3000 non-sprite primitives drawn to the main framebuffer |

`PS2X_VU1_BLOCK_LIST=file` appends each VU1 block the game compiles to `file`, as lines for `vu1_blocks.txt`. Add
the new lines there and the next build generates code for those blocks too; repeated lines are fine.

`PS2X_GS_THREADS=n` draws with `n` GS worker threads, and 0 draws on the game thread. By default it uses the cores
the game and window threads leave free, up to 6. `PS2X_VU1_THREAD=0` or `1` turns VIF1, VU1 and the GIF's own
thread off or on; by default it is on with 6 or more cores.

Keyboard: Enter is START, X is Cross, Z is Square; F1 shows the debug panel. A gamepad works too, and the
keyboard keeps working while one is connected.

## Status

With the full disc, the game plays the EA SPORTS BIG logo movie, shows the title screen, and takes keyboard
input through the front end to a race. In the race, the HUD, sky, mountains, start-gate stadium, riders, their
shadows and the course draw with the right textures, and the race plays from the gate down the first slope.
Sound plays through the PC's audio device: the music, and the radio track shown at the start of a race. The game
makes sound only as fast as it runs, so while it runs slower than the PS2 the sound comes in short runs with gaps.

It is far from full speed. On a 4-core 2.1 GHz Xeon, a race draws about 15 to 16 frames a second. There the two
GS worker threads still set the pace.

When a guest address with no function is reached, the scheduler prints its last 64 dispatches (`[sched-trace]`).
