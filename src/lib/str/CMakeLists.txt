create_test_and_nontest(
        NAME libstring
        FILE_SRCS
            src/KString.cpp
        INCLUDE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        LIBRARIES
            KFS::include
            KFS::core
)

add_library(KFS::Lib::string ALIAS libstring)
add_library(KFS::Lib::string-test ALIAS libstring-test)

add_subdirectory(tests)