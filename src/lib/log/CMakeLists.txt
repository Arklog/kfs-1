add_library(log OBJECT
        log.cpp
)
target_include_directories(log PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(log PRIVATE ${KFLAGS})