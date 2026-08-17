################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

create_test_and_nontest(
        NAME container
        FILE_SRCS
            src/Container.cpp
        INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(KFS::Lib::container ALIAS container)
add_library(KFS::Lib::container-test ALIAS container-test)