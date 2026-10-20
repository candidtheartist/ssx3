# Brings the PS2Recomp checkout in SRC to its commit plus the patch in PATCH, rewriting only the files whose
# contents change, so an updated patch rebuilds only what it touches.
# usage: cmake -DSRC=<checkout> -DPATCH=<patch> -P apply_patch.cmake
find_package(Git REQUIRED QUIET)

function(git)
    execute_process(COMMAND ${CMAKE_COMMAND} -E env "GIT_INDEX_FILE=${index}" "${GIT_EXECUTABLE}" ${ARGN}
                    WORKING_DIRECTORY "${SRC}" RESULT_VARIABLE result OUTPUT_VARIABLE out ERROR_VARIABLE err)
    if(NOT result EQUAL 0)
        message(FATAL_ERROR "git ${ARGN} failed:\n${err}")
    endif()
    set(out "${out}" PARENT_SCOPE)
endfunction()

# The patched tree, built in an index of its own, so the checkout's files and git's own index stay as they are.
execute_process(COMMAND "${GIT_EXECUTABLE}" rev-parse --git-path ssx3pc-patched-index
                WORKING_DIRECTORY "${SRC}" OUTPUT_VARIABLE index OUTPUT_STRIP_TRAILING_WHITESPACE)
get_filename_component(index "${index}" ABSOLUTE BASE_DIR "${SRC}")
file(REMOVE "${index}")
git(read-tree HEAD)
git(apply --cached "${PATCH}")

# Then only the files that differ from it are written out.
git(-c core.quotePath=false diff --name-only --ignore-submodules)
string(REGEX REPLACE "\n$" "" out "${out}")
string(REPLACE "\n" ";" changed "${out}")
if(changed)
    git(checkout-index -f -- ${changed})
endif()
list(LENGTH changed count)
message(STATUS "ps2recomp.patch: ${count} files updated")
file(REMOVE "${index}")
