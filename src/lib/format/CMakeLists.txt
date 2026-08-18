create_test_and_nontest(
        NAME format
        FILE_SRCS
            src/format.cpp
        INCLUDE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        LIBRARIES
            KFS::include
            KFS::Lib::string
            KFS::include
)

add_library(KFS::Lib::format ALIAS format)
add_library(KFS::Lib::format-test ALIAS format-test)

add_subdirectory(tests)