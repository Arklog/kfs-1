add_executable(test_logging
        logging.cpp
)
target_include_directories(test_logging PRIVATE ${CMAKE_SOURCE_DIR}/src .)
target_link_libraries(test_logging PRIVATE
        Catch2::Catch2WithMain
        format
        libstring
        logging_test
)
target_compile_options(test_logging PRIVATE -m32)
target_compile_options(test_logging PUBLIC -DMONITOR_MACRO=std::ofstream)
catch_discover_tests(test_logging)