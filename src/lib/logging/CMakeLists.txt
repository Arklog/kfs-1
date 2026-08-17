create_test_and_nontest(
        NAME logging_generated
        FILE_SRCS
            src/logging.cpp
        INCLUDE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        LIBRARIES
            format
            libstring
)

add_library(KFS::Lib::logging ALIAS logging_generated)
add_library(KFS::Lib::logging-test ALIAS logging_generated-test)

add_subdirectory(tests)