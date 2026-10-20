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

cmake_minimum_required(VERSION 3.24)
project(ssx3pc_recomp NONE)

set(SSX3PC_ELF "" CACHE FILEPATH "Path to the retail SLUS_207.72 (never commit it)")
if(NOT EXISTS "${SSX3PC_ELF}")
    message(FATAL_ERROR "Set SSX3PC_ELF to the retail SLUS_207.72.")
endif()

set(PS2RECOMP_REPOSITORY "https://github.com/ran-j/PS2Recomp.git" CACHE STRING "PS2Recomp repository")
set(PS2RECOMP_COMMIT "eb8688b2fd191129f103a39543002c005b33409c" CACHE STRING
    "PS2Recomp commit that ps2recomp.patch applies to")
set(SSX3PC_PYTHON "${CMAKE_CURRENT_SOURCE_DIR}/../../venv/bin/python" CACHE FILEPATH
    "Python with spimdisasm installed (the decomp's venv by default)")
set(SSX3PC_RUNTIME_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Build type of the runtime")
set(SSX3PC_RUNTIME_JOBS "" CACHE STRING
    "Parallel jobs for the runtime build (the generated code needs about 3 GB per job)")
option(SSX3PC_FFMPEG "Build the runtime with FFmpeg, which plays the game's movies" ON)
# The function tracker logs and flushes every guest function entry and exit to ps2_log.txt,
# which makes races run at 1-2 frames a second. Off unless debugging the runtime.
option(SSX3PC_TRACE_LOGS "Build the runtime with its per-function trace and IOP RPC trace logs" OFF)
set(SSX3PC_PKG_CONFIG_PATH "/usr/lib/i386-linux-gnu/pkgconfig" CACHE STRING
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
    BUILD_BYPRODUCTS "${TOOLS_DIR}/ps2xRecomp/ps2_recomp")

# 3. Function boundaries from spimdisasm, named from the decomp's symbols.
add_custom_command(
    OUTPUT "${FUNCS_CSV}"
    COMMAND "${SSX3PC_PYTHON}" -m spimdisasm elfObjDisasm
            --instr-category r5900
            --function-info "${CMAKE_CURRENT_BINARY_DIR}/funcinfo.csv"
            --symbol-addrs "${CMAKE_CURRENT_SOURCE_DIR}/../../config/symbol_addrs.txt"
            "${SSX3PC_ELF}" "${CMAKE_CURRENT_BINARY_DIR}/disasm"
    COMMAND "${SSX3PC_PYTHON}" "${CMAKE_CURRENT_SOURCE_DIR}/gen_funcs.py"
            "${CMAKE_CURRENT_BINARY_DIR}/funcinfo.csv"
            "${CMAKE_CURRENT_SOURCE_DIR}/function_splits.txt"
            "${FUNCS_CSV}"
    DEPENDS "${SSX3PC_ELF}"
            "${CMAKE_CURRENT_SOURCE_DIR}/gen_funcs.py"
            "${CMAKE_CURRENT_SOURCE_DIR}/function_splits.txt"
            "${CMAKE_CURRENT_SOURCE_DIR}/../../config/symbol_addrs.txt"
    COMMENT "Finding function boundaries in SLUS_207.72"
    VERBATIM)

# The config keeps the analyzer's stub and entry lists; only paths are filled in.
# (string(REPLACE) rather than configure_file: the lists are full of name@address.)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/ssx3.toml.in" SSX3_TOML)
string(REPLACE "@SSX3PC_ELF@" "${SSX3PC_ELF}" SSX3_TOML "${SSX3_TOML}")
string(REPLACE "@FUNCS_CSV@" "${FUNCS_CSV}" SSX3_TOML "${SSX3_TOML}")
string(REPLACE "@GEN_DIR@" "${GEN_DIR}" SSX3_TOML "${SSX3_TOML}")
file(CONFIGURE OUTPUT "${CONFIG_TOML}" CONTENT "${SSX3_TOML}" @ONLY)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ssx3.toml.in")

# 4. Translate the ELF to C++.
add_custom_command(
    OUTPUT "${GEN_DIR}/register_functions.cpp"
    COMMAND ${CMAKE_COMMAND} -E rm -rf "${GEN_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${GEN_DIR}"
    COMMAND "${TOOLS_DIR}/ps2xRecomp/ps2_recomp" "${CONFIG_TOML}"
    DEPENDS ps2recomp_tools "${FUNCS_CSV}" "${CONFIG_TOML}" "${SSX3PC_ELF}"
    COMMENT "Recompiling SLUS_207.72"
    VERBATIM)
add_custom_target(ssx3_recompiled DEPENDS "${GEN_DIR}/register_functions.cpp")

# 5. The 32-bit runtime with the generated code and our overrides.
if(SSX3PC_FFMPEG)
    set(RUNTIME_FFMPEG ON)
    set(RUNTIME_ENV ${CMAKE_COMMAND} -E env "PKG_CONFIG_PATH=${SSX3PC_PKG_CONFIG_PATH}")
else()
    set(RUNTIME_FFMPEG OFF)
    set(RUNTIME_ENV "")
endif()
set(RUNTIME_BUILD_ARGS --target ps2EntryRunner)
if(SSX3PC_RUNTIME_JOBS)
    list(APPEND RUNTIME_BUILD_ARGS -j ${SSX3PC_RUNTIME_JOBS})
endif()
ExternalProject_Add(ssx3pc_runtime
    DEPENDS ps2recomp_src ssx3_recompiled
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
        "-DPS2X_VU1_BLOCK_ELF=${SSX3PC_ELF}"
    BUILD_COMMAND ${RUNTIME_ENV} ${CMAKE_COMMAND} --build . ${RUNTIME_BUILD_ARGS}
    BUILD_ALWAYS ON
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/runtime/ps2xRuntime/ps2EntryRunner")
