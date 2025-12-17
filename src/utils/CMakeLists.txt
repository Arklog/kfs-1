################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

add_library(libutils STATIC
        KArray.cpp
        KArray.hpp
)
target_compile_options(libutils PRIVATE
        ${KERN_COMPILER_FLAGS}
)