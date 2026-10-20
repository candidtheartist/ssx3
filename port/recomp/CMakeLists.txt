# SPDX-License-Identifier: GPL-3.0-or-later
#
# Builds SSX 3 on the PS2Recomp runtime: the retail ELF is translated to C++
# at build time and linked against a patched, 32-bit PS2Recomp runtime.
# Nothing generated here is ever committed; it all lives in the build tree.
#
#   cmake -S port/recomp -B port/recomp/build -G Ninja -DSSX3PC_ELF=/path/to/SLUS_207.72
#   ninja -C port/recomp/build
#
# This is a separate project from port/ because the translator tools are
# built for the host (64-bit) while the runtime is built 32-bit.
# On Windows, run it from an MSYS2 MINGW32 shell: everything is built with
# that 32-bit MinGW toolchain (see README.md).

cmake_minimum_required(VERSION 3.24)
project(ssx3pc_recomp NONE)

set(SSX3PC_ELF "" CACHE FILEPATH "Path to the retail SLUS_207.72 (never commit it)")
if(NOT EXISTS "${SSX3PC_ELF}")
    message(FATAL_ERROR "Set SSX3PC_ELF to the retail SLUS_207.72.")
endif()
# Forward slashes, so a Windows path also works inside the TOML config.
file(TO_CMAKE_PATH "${SSX3PC_ELF}" SSX3PC_ELF_PATH)

set(PS2RECOMP_REPOSITORY "https://github.com/ran-j/PS2Recomp.git" CACHE STRING "PS2Recomp repository")
set(PS2RECOMP_COMMIT "eb8688b2fd191129f103a39543002c005b33409c" CACHE STRING
    "PS2Recomp commit that ps2recomp.patch applies to")
# A venv keeps python in bin/, except one made by python.org's Windows Python, which uses Scripts/.
set(SSX3PC_DEFAULT_PYTHON "${CMAKE_CURRENT_SOURCE_DIR}/../../venv/bin/python")
if(CMAKE_HOST_WIN32 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../venv/Scripts/python.exe")
    set(SSX3PC_DEFAULT_PYTHON "${CMAKE_CURRENT_SOURCE_DIR}/../../venv/Scripts/python.exe")
endif()
set(SSX3PC_PYTHON "${SSX3PC_DEFAULT_PYTHON}" CACHE FILEPATH
    "Python with spimdisasm installed (the decomp's venv by default)")
set(SSX3PC_RUNTIME_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Build type of the runtime")
set(SSX3PC_RUNTIME_JOBS "" CACHE STRING
    "Parallel jobs for the runtime build (the generated code needs about 3 GB per job)")
option(SSX3PC_FFMPEG "Build the runtime with FFmpeg, which plays the game's movies" ON)
# The function tracker logs and flushes every guest function entry and exit to ps2_log.txt,
# which makes races run at 1-2 frames a second. Off unless debugging the runtime.
option(SSX3PC_TRACE_LOGS "Build the runtime with its per-function trace and IOP RPC trace logs" OFF)
if(WIN32)
    # MSYS2's pkg-config already looks in its own MINGW32 prefix.
    set(SSX3PC_DEFAULT_PKG_CONFIG_PATH "")
else()
    set(SSX3PC_DEFAULT_PKG_CONFIG_PATH "/usr/lib/i386-linux-gnu/pkgconfig")
endif()
set(SSX3PC_PKG_CONFIG_PATH "${SSX3PC_DEFAULT_PKG_CONFIG_PATH}" CACHE STRING
    "pkg-config path for the 32-bit FFmpeg libraries")

include(ExternalProject)

set(SRC_DIR "${CMAKE_CURRENT_BINARY_DIR}/ps2recomp")
set(GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(FUNCS_CSV "${CMAKE_CURRENT_BINARY_DIR}/funcs.csv")
set(CONFIG_TOML "${CMAKE_CURRENT_BINARY_DIR}/ssx3.toml")
set(TOOLS_DIR "${CMAKE_CURRENT_BINARY_DIR}/tools")

# 1. PS2Recomp at a fixed commit, with our runtime changes applied.
ExternalProject_Add(ps2recomp_src
    GIT_REPOSITORY "${PS2RECOMP_REPOSITORY}"
    GIT_TAG "${PS2RECOMP_COMMIT}"
    GIT_SUBMODULES_RECURSE ON
    SOURCE_DIR "${SRC_DIR}"
    # LF line endings whatever git's settings, so the patch applies on Windows too.
    GIT_CONFIG core.autocrlf=false
    UPDATE_COMMAND ""
    PATCH_COMMAND git apply "${CMAKE_CURRENT_SOURCE_DIR}/ps2recomp.patch"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "")

# 2. The translator, built for the host.
ExternalProject_Add(ps2recomp_tools
    DEPENDS ps2recomp_src
    DOWNLOAD_COMMAND ""
    SOURCE_DIR "${SRC_DIR}"
    BINARY_DIR "${TOOLS_DIR}"
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DPS2X_BUILD_RECOMP=ON
        -DPS2X_BUILD_ANALYZER=OFF
        -DPS2X_BUILD_RUNTIME=OFF
        -DPS2X_BUILD_TEST=OFF
        -DPS2X_BUILD_STUDIO=OFF
    BUILD_COMMAND ${CMAKE_COMMAND} --build . --target ps2_recomp
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS "${TOOLS_DIR}/ps2xRecomp/ps2_recomp${CMAKE_EXECUTABLE_SUFFIX}")

# 3. Function boundaries from spimdisasm, named from the decomp's symbols.
add_custom_command(
    OUTPUT "${FUNCS_CSV}"
    COMMAND "${SSX3PC_PYTHON}" -m spimdisasm elfObjDisasm
            --instr-category r5900
            --function-info "${CMAKE_CURRENT_BINARY_DIR}/funcinfo.csv"
            --symbol-addrs "${CMAKE_CURRENT_SOURCE_DIR}/../../config/symbol_addrs.txt"
            "${SSX3PC_ELF_PATH}" "${CMAKE_CURRENT_BINARY_DIR}/disasm"
    COMMAND "${SSX3PC_PYTHON}" "${CMAKE_CURRENT_SOURCE_DIR}/gen_funcs.py"
            "${CMAKE_CURRENT_BINARY_DIR}/funcinfo.csv"
            "${CMAKE_CURRENT_SOURCE_DIR}/function_splits.txt"
            "${FUNCS_CSV}"
    DEPENDS "${SSX3PC_ELF_PATH}"
            "${CMAKE_CURRENT_SOURCE_DIR}/gen_funcs.py"
            "${CMAKE_CURRENT_SOURCE_DIR}/function_splits.txt"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../config/symbol_addrs.txt"
    COMMENT "Finding function boundaries in SLUS_207.72"
    VERBATIM)

# The config keeps the analyzer's stub and entry lists; only paths are filled in.
# (string(REPLACE) rather than configure_file: the lists are full of name@address.)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/ssx3.toml.in" SSX3_TOML)
string(REPLACE "@SSX3PC_ELF@" "${SSX3PC_ELF_PATH}" SSX3_TOML "${SSX3_TOML}")
string(REPLACE "@FUNCS_CSV@" "${FUNCS_CSV}" SSX3_TOML "${SSX3_TOML}")
string(REPLACE "@GEN_DIR@" "${GEN_DIR}" SSX3_TOML "${SSX3_TOML}")
file(CONFIGURE OUTPUT "${CONFIG_TOML}" CONTENT "${SSX3_TOML}" @ONLY)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ssx3.toml.in")

# 4. Translate the ELF to C++.
add_custom_command(
    OUTPUT "${GEN_DIR}/register_functions.cpp"
    COMMAND ${CMAKE_COMMAND} -E rm -rf "${GEN_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${GEN_DIR}"
    COMMAND "${TOOLS_DIR}/ps2xRecomp/ps2_recomp${CMAKE_EXECUTABLE_SUFFIX}" "${CONFIG_TOML}"
    DEPENDS ps2recomp_tools "${FUNCS_CSV}" "${CONFIG_TOML}" "${SSX3PC_ELF_PATH}"
    COMMENT "Recompiling SLUS_207.72"
    VERBATIM)
add_custom_target(ssx3_recompiled DEPENDS "${GEN_DIR}/register_functions.cpp")

# 5. The 32-bit runtime with the generated code and our overrides.
set(RUNTIME_DEPENDS ps2recomp_src ssx3_recompiled)
if(WIN32 AND SSX3PC_FFMPEG)
    # On Windows, a static FFmpeg with only what the game's movies need (the MPEG-2 decoder and the
    # scaler), so the executable needs no FFmpeg DLLs. Built with the MINGW32 shell's sh, make and gcc.
    set(SSX3PC_FFMPEG_REPOSITORY "https://github.com/FFmpeg/FFmpeg.git" CACHE STRING "FFmpeg repository (Windows)")
    set(SSX3PC_FFMPEG_TAG "n7.1.1" CACHE STRING "FFmpeg release tag (Windows)")
    set(FFMPEG_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/ffmpeg")
    ExternalProject_Add(ssx3pc_ffmpeg
        GIT_REPOSITORY "${SSX3PC_FFMPEG_REPOSITORY}"
        GIT_TAG "${SSX3PC_FFMPEG_TAG}"
        GIT_SHALLOW TRUE
        GIT_CONFIG core.autocrlf=false
        UPDATE_COMMAND ""
        CONFIGURE_COMMAND sh <SOURCE_DIR>/configure "--prefix=${FFMPEG_PREFIX}" --arch=x86 --target-os=mingw32
            --disable-everything --disable-programs --disable-doc --disable-network --disable-autodetect
            --disable-x86asm --enable-static --disable-shared
            --enable-decoder=mpeg1video,mpeg2video --enable-parser=mpegvideo --enable-swscale
            "--extra-cflags=-msse4.2 -mfpmath=sse"
        BUILD_COMMAND make -j4
        INSTALL_COMMAND make install)
    list(APPEND RUNTIME_DEPENDS ssx3pc_ffmpeg)
    set(SSX3PC_PKG_CONFIG_PATH "${FFMPEG_PREFIX}/lib/pkgconfig")
endif()
if(SSX3PC_FFMPEG)
    set(RUNTIME_FFMPEG ON)
    if(SSX3PC_PKG_CONFIG_PATH)
        set(RUNTIME_ENV ${CMAKE_COMMAND} -E env "PKG_CONFIG_PATH=${SSX3PC_PKG_CONFIG_PATH}")
    else()
        set(RUNTIME_ENV "")
    endif()
else()
    set(RUNTIME_FFMPEG OFF)
    set(RUNTIME_ENV "")
endif()
set(RUNTIME_BUILD_ARGS --target ps2EntryRunner)
if(SSX3PC_RUNTIME_JOBS)
    list(APPEND RUNTIME_BUILD_ARGS -j ${SSX3PC_RUNTIME_JOBS})
endif()
ExternalProject_Add(ssx3pc_runtime
    DEPENDS ${RUNTIME_DEPENDS}
    DOWNLOAD_COMMAND ""
    SOURCE_DIR "${SRC_DIR}"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/runtime"
    CMAKE_COMMAND ${RUNTIME_ENV} ${CMAKE_COMMAND}
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${SSX3PC_RUNTIME_BUILD_TYPE}
        "-DCMAKE_C_FLAGS=-m32 -msse4.2 -mfpmath=sse"
        "-DCMAKE_CXX_FLAGS=-m32 -msse4.2 -mfpmath=sse"
        -DCMAKE_EXE_LINKER_FLAGS=-m32
        -DPS2X_BUILD_RECOMP=OFF
        -DPS2X_BUILD_ANALYZER=OFF
        -DPS2X_BUILD_RUNTIME=ON
        -DPS2X_BUILD_TEST=OFF
        -DPS2X_BUILD_STUDIO=OFF
        -DPS2X_ENABLE_FFMPEG=${RUNTIME_FFMPEG}
        -DPS2X_ENABLE_SCCACHE=OFF
        -DPS2X_ENABLE_AGRESSIVE_LOGS=${SSX3PC_TRACE_LOGS}
        -DPS2X_ENABLE_IOP_RPC_TRACE=${SSX3PC_TRACE_LOGS}
        -DPS2X_RUNNER_SOURCE_DIR=${GEN_DIR}
        -DPS2X_RUNNER_EXTRA_SOURCES=${CMAKE_CURRENT_SOURCE_DIR}/ssx3_overrides.cpp
        -DPS2X_VU1_BLOCK_LIST=${CMAKE_CURRENT_SOURCE_DIR}/vu1_blocks.txt
        "-DPS2X_VU1_BLOCK_ELF=${SSX3PC_ELF_PATH}"
    BUILD_COMMAND ${RUNTIME_ENV} ${CMAKE_COMMAND} --build . ${RUNTIME_BUILD_ARGS}
    BUILD_ALWAYS ON
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/runtime/ps2xRuntime/ps2EntryRunner${CMAKE_EXECUTABLE_SUFFIX}")
