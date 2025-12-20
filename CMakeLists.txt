cmake_minimum_required(VERSION 3.5)
project(kfs-1)

set(CMAKE_CXX_STANDARD 23)

##################################
# Install external dependencies
##################################

include(FetchContent)

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.11.0
)

FetchContent_MakeAvailable(
        catch2
)

##################################
# Some variables
##################################
#target_compile_options(Catch2 PUBLIC -m32)
#target_compile_options(Catch2WithMain PUBLIC -m32)

set(KERN_COMPILER_FLAGS
    -O2
    -m32
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    -Wno-unused-parameter
    -Wno-missing-field-initializers
    -ffreestanding
    -fno-builtin
    -fno-stack-protector
    -fpie
    -fno-exceptions
    -fno-rtti
    -nostdlib
    -nostdinc
)

##################################
# Main source code
##################################

add_subdirectory(src)

##################################
# Tests
##################################

include(CTest)
include(Catch)
target_compile_options(Catch2 PUBLIC -m32)
target_link_options(Catch2 PUBLIC -m32)
target_compile_options(Catch2WithMain PUBLIC -m32)
target_link_options(Catch2WithMain PUBLIC -m32)
enable_testing()
add_subdirectory(tests)