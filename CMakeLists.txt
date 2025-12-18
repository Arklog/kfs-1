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
    -fno-exceptions
    -fno-rtti
    -nostdlib
    -nostdinc
)

##################################
# Main source code
##################################

add_subdirectory(src)
#set(CMAKE_LINKER ld)
#set(CMAKE_ASM_LINK_EXECUTABLE /usr/bin/ld)
#enable_language(ASM_NASM)
#enable_language(ASM)
#add_executable(kfs-1
#        src/bootloader.s
#)
#target_link_libraries(kfs-1 PRIVATE kernel)
#set_target_properties(kfs-1 PROPERTIES LINKER_LANGUAGE ASM)
#target_link_options(kfs-1 PRIVATE -T ${CMAKE_SOURCE_DIR}/src/linker.ld -e start -m elf_i386)

##################################
# Tests
##################################

enable_testing()
add_subdirectory(tests)