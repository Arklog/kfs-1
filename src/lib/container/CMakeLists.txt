################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

add_library(container STATIC
        KArray.cpp
        KArray.hpp
        Iterator.cpp
        Iterator.hpp
        Container.cpp
        Container.hpp
)
target_compile_options(container PRIVATE
        ${KERN_COMPILER_FLAGS}
)