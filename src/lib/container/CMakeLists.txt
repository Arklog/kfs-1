################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

add_library(container STATIC
        Array.cpp
        Array.hpp
        Iterator.cpp
        Iterator.hpp
        Container.cpp
        Container.hpp
        StackVector.hpp
        StackVector.cpp
)
target_include_directories(container PRIVATE ${CMAKE_SOURCE_DIR}/src .)
target_link_libraries(container PRIVATE libstring)
target_compile_options(container PRIVATE
        ${KERN_COMPILER_FLAGS}
)
