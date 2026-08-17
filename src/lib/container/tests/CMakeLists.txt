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
        KFS::Lib::container-test
        KFS::Lib::utility-test
        Catch2::Catch2WithMain
)
target_compile_options(
        test_container
        PRIVATE
        -m32
)
target_compile_definitions(test_container PRIVATE KFS_HOST_TEST)

catch_discover_tests(test_container)