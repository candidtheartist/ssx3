# Native game code

This is the first step from the static recompilation toward a native port. Some of SSX 3's own functions run in the PC
build as code compiled from the decompiled C in `../../../src`, not as code translated from the retail executable.
These native functions replace their recompiled copies at startup, and the rest of the game keeps running recompiled.

## How it works

- `select_native.py` decides which functions can run natively and writes `native_functions.txt` and
  `native_symbols.txt`. Both files are committed. It needs a full decomp build (it reads `obj/` and
  `out/SLUS_207.72.map`) and pyelftools, so it is run by hand whenever matching moves on:

  ```bash
  ninja                                              # the decomp, from the repository root
  python port/recomp/native/select_native.py         # with pyelftools installed
  ```

- At build time, `gen_native.py` compiles each listed unit for the 32-bit host with `native_flags.py`'s flags. It adds an
  entry point per picked function (`native_abi.h`) and links everything into one object. In that object only the
  function table is global, so game symbols can't clash with the runtime's or the C library's.
- `../ssx3_native.cpp` swaps the native functions in with `replaceFunction`. Each entry point reads its arguments from
  the EE registers, following the EE EABI: ints and pointers in a0–a3 and t0–t3, floats in f12–f19, each kind counted on
  its own. It writes the result to v0 or f0.
- Native code works on the game's memory directly. EE RAM is mapped at its PS2 addresses in the 32-bit process, so a
  pointer the game stored is a valid host pointer. Every global the C refers to resolves to its address in the retail
  executable.

## Which functions qualify

A function is picked only when its native copy is certain to do what the recompiled one does:

- It is matched C (no `INCLUDE_ASM`) in a unit the host compiler builds.
- Its EE code makes no system call or indirect call, and has no COP0, VU0 or MMI instruction or hardware register
  address.
- Its arguments and result are ints, pointers or floats, at most 8 of each kind. It never uses `long`, `long long`,
  `double` or `bool`, whose sizes differ between the EE and the host.
- On the host it touches no data its own unit defines, since that copy would not be the game's. It may use globals the
  unit declares `extern`, plus the compiler's own constants and jump tables.
- Everything it calls is picked too, or is a C library function the host does the same job with (`strlen`,
  `memcpy`, ...).

The last rule is the big limit for now. The runtime switches EE threads by unwinding the host stack back to its
scheduler and later re-entering the recompiled code at the saved PC. That would lose a native caller's frame, so native
code must never call into recompiled code. Lifting this needs each EE thread to run on its own host stack; after that,
most of the remaining matched functions can go native too.

## Checking it

`PS2X_NATIVE_CHECK=n` runs the first `n` calls of every native function both ways, from the same RAM and registers. It
then reports any EE RAM word or result that differs between the two. `PS2X_NATIVE=0` turns native code off at run time.
The `SSX3PC_NATIVE=OFF` CMake option leaves it out of the build.
