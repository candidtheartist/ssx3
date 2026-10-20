# SSX 3 PC port

Everything under `port/` is licensed under the GNU GPL v3 or later ([LICENSE](LICENSE)), because it links
PS2Recomp's GPL-3 runtime. The decompilation outside `port/` keeps its own license.

This directory is the start of a native PC build of SSX 3. It holds two things:

- **`recomp/`** builds the game on the [PS2Recomp](https://github.com/ran-j/PS2Recomp) runtime: the retail
  ELF is translated to C++ at build time and linked against a patched 32-bit runtime. This boots the game
  today, but it is mostly a static recompilation with a runtime that stands in for the PS2 hardware, not a
  native port. The exception is a first set of game functions compiled from the decompiled C and run
  natively in place of their recompiled copies ([recomp/native](recomp/native/README.md)). See
  [recomp/README.md](recomp/README.md).
- **`src/`** is the native platform layer that the decompiled code will run on. It doesn't run game code yet.

The native platform layer:

- **`src/ps2os/eemem`** maps EE memory at its PS2 addresses inside a 32-bit process: main RAM from
  `0x00100000`, its uncached mirrors at `0x20100000` and `0x30100000`, and the scratchpad at `0x70000000`.
  The decompiled C, and later the recompiled asm, use EE addresses as pointers, so with this mapping a
  pointer read from game memory is a valid host pointer. It also loads `SLUS_207.72` into that memory.
- **`src/ps2os/kernel`** provides threads, semaphores and the VSync interrupt on SDL3. EE code runs only while
  holding a single "CPU" lock, so the game still sees one processor.
- **`src/platform/ds2pad`** and **`sdlpad`** build the DualShock 2 packet `scePadRead` returns, from an SDL
  gamepad or the keyboard. The game's own conversion then turns it into its 24 input channels.
- **`src/main.c`** opens a window, runs a 60 Hz VSync and an EE thread that logs controller packets.

The plan this follows, and the milestones after it, are in the project's port plan
(`plans/native-pc-port-plan.md` in the project files). The next step is M1: compile the matched C from
`../src` with `PLATFORM_PC` and link it here.

## Building

The port is always 32-bit. The decompiled code reads struct fields at fixed 32-bit offsets and stores EE
addresses as pointers.

Debian/Ubuntu:

```bash
sudo dpkg --add-architecture i386 && sudo apt update
sudo apt install gcc-multilib cmake ninja-build libx11-dev:i386 libxext-dev:i386
cmake -S port -B port/build -G Ninja
ninja -C port/build
ctest --test-dir port/build
```

CMake fetches SDL 3.2.8 and builds it statically. Pass `-DSSX3PC_SYSTEM_SDL=ON` to use an installed 32-bit
SDL3 instead.

Windows: configure with `cmake -S port -B port/build -A Win32`. The Windows memory mapping is written but has
not been built or tested yet.

## Running

```bash
port/build/ssx3pc                                  # window, logs controller input
port/build/ssx3pc --elf disc/SLUS_207.72           # also loads the game executable into EE memory
port/build/ssx3pc --headless --frames 120          # no window; host and EE thread run in lockstep
```

To include the retail executable in the tests, configure with `-DSSX3PC_ELF=/path/to/SLUS_207.72`. That adds a
test that loads it and checks the segment and bss. Never commit the executable or any disc files to this
repository.

## Known limits

- **AddressSanitizer can't be used.** On 32-bit Linux its shadow memory sits at `0x20000000`..`0x3FFFFFFF`,
  which is where the uncached RAM mirrors have to go. UndefinedBehaviorSanitizer works.
- **Thread priorities are not modelled.** When several EE threads are ready, whichever takes the lock runs.
  The EE scheduler always runs the highest-priority ready thread, so this will need to change once real game
  threads run here.
- **The kernel calls are not the `sce*` ones.** A compatibility layer will map the library calls in the ELF
  onto these once they are identified.
