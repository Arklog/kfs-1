add_library(logging OBJECT
        logging.cpp
)
target_include_directories(logging PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(logging PRIVATE ${KFLAGS})

add_library(logging_test OBJECT logging.cpp)
target_include_directories(logging_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(logging_test PRIVATE -m32 -DMONITOR_MACRO=std::fstream)