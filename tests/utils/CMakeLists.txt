################################################
# CMakeLists.txt for utils tests
# This file sets up the test executable for the utils library
################################################

add_executable(test_utils
        KArray.cpp
)
target_link_libraries(test_utils
        PRIVATE
        libutils
        Catch2::Catch2WithMain
)
target_include_directories(
        test_utils
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)
add_dependencies(
        test_utils
        Catch2::Catch2WithMain
        libutils
)
