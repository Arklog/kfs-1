create_test_and_nontest(
        NAME format
        FILE_SRCS
            format.cpp
        INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src
        LIBRARIES
            KFS::include
)

add_library(KFS::Lib::format ALIAS format)
add_library(KFS::Lib::format-test ALIAS format-test)

add_subdirectory(tests)