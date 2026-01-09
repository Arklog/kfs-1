add_library(libport OBJECT
        port.cpp
)
target_compile_options(libport PRIVATE ${KERN_COMPILER_FLAGS})
target_include_directories(libport PRIVATE ${CMAKE_SOURCE_DIR}/src)