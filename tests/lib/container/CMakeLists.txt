################################################
# CMakeLists.txt for utils tests
# This file sets up the test executable for the utils library
################################################

add_executable(test_container
        Array.cpp
        iterator/ContiguousIterator.cpp
        StackVector.cpp
        static_check.hpp
        iterator/PairIterator.cpp
        range.cpp
)
target_link_libraries(test_container
        PRIVATE
        container
        Catch2::Catch2WithMain
)
target_include_directories(
        test_container
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)
target_compile_options(
        test_container
        PRIVATE
        -m32
)

catch_discover_tests(test_container)