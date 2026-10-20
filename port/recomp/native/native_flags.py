# SPDX-License-Identifier: GPL-3.0-or-later
"""Host compiler flags for the decompiled C, shared by select_native.py and gen_native.py.

32-bit, as on the EE. -malign-double gives long long and double the EE's 8-byte
alignment inside structs. -fwrapv and -fno-strict-aliasing match how the
decomp's C is written (raw offsets, int/pointer casts). SKIP_ASM turns
INCLUDE_ASM into nothing.
"""
HOST_CXXFLAGS = [
    "-m32", "-std=gnu++17", "-fpermissive", "-w", "-O2",
    "-ffunction-sections", "-fdata-sections", "-fPIC",
    "-fno-strict-aliasing", "-fwrapv", "-malign-double",
    "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-msse2", "-mfpmath=sse",
    "-DSKIP_ASM", "-DPLATFORM_PC",
]
