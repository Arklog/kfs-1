add_executable(test_utility
        utility.cpp
)
target_include_directories(test_utility PRIVATE ${CMAKE_SOURCE_DIR}/src .)
target_link_libraries(test_utility PRIVATE Catch2::Catch2WithMain)
target_compile_options(test_utility PRIVATE -m32)
target_link_options(test_utility PRIVATE -m32)
target_compile_definitions(test_utility PRIVATE KFS_HOST_TEST)
catch_discover_tests(test_utility)