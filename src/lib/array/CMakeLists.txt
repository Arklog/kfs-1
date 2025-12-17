################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

add_library(libarray STATIC
        KArray.cpp
        KArray.hpp
)
target_compile_options(libarray PRIVATE
        ${KERN_COMPILER_FLAGS}
)