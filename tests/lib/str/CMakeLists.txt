################################################
# CMakeLists.txt for utils tests
# This file sets up the test executable for the utils library
################################################

add_executable(test_string
        KString.cpp
)
target_link_libraries(test_string
        PRIVATE
        libstring
        Catch2::Catch2WithMain
)
target_include_directories(
        test_string
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

catch_discover_tests(test_string)