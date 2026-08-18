################################################
# CMakeLists.txt for utils library
# This file sets up the utils static library
################################################

create_test_and_nontest(
        NAME container_generated
        FILE_SRCS
            src/Container.cpp
        INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include
        LIBRARIES
            KFS::Lib::utility
)

add_library(KFS::Lib::container ALIAS container_generated)
add_library(KFS::Lib::container-test ALIAS container_generated-test)

add_subdirectory(tests)