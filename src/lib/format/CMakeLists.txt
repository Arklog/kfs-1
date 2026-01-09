add_library(format OBJECT
    format.cpp
)
target_compile_options(format PRIVATE ${KERN_COMPILER_FLAGS})
target_include_directories(format PUBLIC ${CMAKE_SOURCE_DIR}/src)