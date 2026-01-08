################################################
# CMakeLists.txt for utils tests
# This file sets up the test executable for the utils library
################################################

add_executable(test_array
        Array.cpp
        Iterator.cpp
        StackVector.cpp
        static_check.hpp
)
target_link_libraries(test_array
        PRIVATE
        container
        Catch2::Catch2WithMain
)
target_include_directories(
        test_array
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)
target_compile_options(
        test_array
        PRIVATE
        -m32
        -fdiagnostics-all-candidates
)

catch_discover_tests(test_array)