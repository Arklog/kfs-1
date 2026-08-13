#add_library(libport STATIC
#        port.cpp
#)
#target_compile_options(libport PRIVATE ${KFLAGS})
#target_include_directories(libport PRIVATE ${CMAKE_SOURCE_DIR}/src)
#set_target_properties(libport PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})

create_test_and_nontest(
        NAME libport
        FILE_SRCS port.cpp
        INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src
        LIBRARIES
)