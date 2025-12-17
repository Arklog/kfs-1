################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

add_library(libutils STATIC
        KArray.cpp
        KArray.hpp
)
target_compile_options(libutils PRIVATE
        -ffreestanding
        -fno-builtin
        -fno-stack-protector
        -fno-pie -no-pie
        -fno-exceptions
        -fno-rtti
        -nostdlib
        -nostdinc
)