################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

add_library(container INTERFACE)

target_sources(container INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/Array.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Container.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Container.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StackVector.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/iterator/Iterator.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/iterator/ContiguousIterator.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/concept.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/range.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/iterator/PairIterator.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pair.hpp
)
target_include_directories(container INTERFACE ${CMAKE_SOURCE_DIR}/src .)
#target_compile_options(container PRIVATE ${KFLAGS})