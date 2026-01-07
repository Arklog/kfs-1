################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

add_library(container OBJECT
        Array.cpp
        Array.hpp
        Container.cpp
        Container.hpp
        Iterator.cpp
        Iterator.hpp
        StackVector.hpp
        StackVector.cpp
)
target_include_directories(container PRIVATE ${CMAKE_SOURCE_DIR}/src .)
target_link_libraries(container PRIVATE libstring)
target_compile_options(container PRIVATE
        ${KFLAGS}
)
