cmake_minimum_required(VERSION 3.10)
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

set(KFLAGS
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

if (NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    message("CMAKE_BUILD_TYPE UNDEFINED")
    set(CMAKE_BUILD_TYPE Release)
endif ()

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(KFLAGS ${KFLAGS} -O0)
else ()
    set(KFLAGS ${KFLAGS} -O2)
endif ()

##################################
# Main source code
##################################

add_subdirectory(src)

##################################
# Tests
##################################

include(CTest)
include(Catch)

# Force 32bit catch2 compilation
target_compile_options(Catch2 PUBLIC -m32)
target_link_options(Catch2 PUBLIC -m32)
target_compile_options(Catch2WithMain PUBLIC -m32)
target_link_options(Catch2WithMain PUBLIC -m32)

enable_testing()
add_subdirectory(tests)