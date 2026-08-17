add_executable(test_logging
        logging.cpp
)
target_link_libraries(test_logging PRIVATE
        Catch2::Catch2WithMain
        KFS::Lib::logging-test
)
target_compile_options(test_logging PRIVATE -m32)
target_compile_definitions(test_logging PUBLIC KFS_HOST_TEST)
catch_discover_tests(test_logging)