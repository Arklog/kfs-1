################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

create_test_and_nontest(
        NAME container
        FILE_SRCS
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
        INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src
)
