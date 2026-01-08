################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

add_library(container OBJECT
        Array.cpp
        Array.hpp
        Container.cpp
        Container.hpp
        StackVector.hpp
        StackVector.cpp
        iterator/Iterator.cpp
        iterator/Iterator.hpp
        iterator/ContiguousIterator.hpp
        iterator/ContiguousIterator.cpp
)
target_include_directories(container PRIVATE ${CMAKE_SOURCE_DIR}/src .)
target_link_libraries(container PRIVATE libstring)
target_compile_options(container PRIVATE
        ${KFLAGS}
)
