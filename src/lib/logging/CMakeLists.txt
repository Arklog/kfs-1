add_library(logging OBJECT
        logging.cpp
)
target_include_directories(logging PRIVATE . ${CMAKE_SOURCE_DIR}/src)
target_compile_options(logging PRIVATE ${KFLAGS})