#add_library(libport STATIC
#        port.cpp
#)
#target_compile_options(libport PRIVATE ${KFLAGS})
#target_include_directories(libport PRIVATE ${CMAKE_SOURCE_DIR}/src)
#set_target_properties(libport PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})

create_test_and_nontest(
        NAME port
        FILE_SRCS src/port.cpp
        INCLUDE_DIR
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        LIBRARIES
            KFS::include
)

add_library(KFS::Lib::port ALIAS port)
add_library(KFS::Lib::port-test ALIAS port-test)
