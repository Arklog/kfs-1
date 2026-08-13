create_test_and_nontest(
        NAME logging
        FILE_SRCS logging.cpp
        INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src
        LIBRARIES format
)