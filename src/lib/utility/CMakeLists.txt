create_test_and_nontest(
        NAME utility_generated
        FILE_SRCS
            src/empty.cpp # header only library, we need at least one source
        INCLUDE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(KFS::Lib::utility ALIAS utility_generated)
add_library(KFS::Lib::utility-test ALIAS utility_generated-test)