################################################
# CMakeLists.txt for utils tests
# This file sets up the test executable for the utils library
################################################

add_executable(test_array
        KArray.cpp
)
target_link_libraries(test_array
        PRIVATE
        libarray
        Catch2::Catch2WithMain
)
target_include_directories(
        test_array
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)
#add_dependencies(
#        test_array
#        Catch2::Catch2WithMain
#        libarray
#)
