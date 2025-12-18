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

set(KERN_COMPILER_FLAGS
    -O2
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

add_executable(kfs-1 src/main.cpp)
target_compile_options(kfs-1 PRIVATE
        ${KERN_COMPILER_FLAGS}
)

##################################
# Tests
##################################

enable_testing()
add_subdirectory(tests)