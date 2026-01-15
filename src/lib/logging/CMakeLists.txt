add_library(logging OBJECT
        logging.cpp
)
target_include_directories(logging PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(logging PRIVATE ${KFLAGS})
set_target_properties(logging PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})

add_library(logging_test OBJECT logging.cpp)
target_include_directories(logging_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(logging_test PRIVATE -m32)
target_compile_definitions(logging_test PRIVATE TEST)