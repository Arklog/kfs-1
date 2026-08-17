create_test_and_nontest(
        NAME math
        FILE_SRCS
            src/math.cpp
        INCLUDE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(KFS::Lib::math ALIAS math)
add_library(KFS::Lib::math-test ALIAS math-test)

add_subdirectory(tests)