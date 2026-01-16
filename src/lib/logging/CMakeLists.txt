add_library(logging STATIC
        logging.cpp
)
target_include_directories(logging PRIVATE . ${CMAKE_SOURCE_DIR}/src)
target_compile_options(logging PRIVATE ${KFLAGS})
target_link_libraries(logging PUBLIC format)
set_target_properties(logging PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})