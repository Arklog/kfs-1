add_library(libstring OBJECT
    KString.cpp
)
target_compile_options(libstring PRIVATE ${KERN_COMPILER_FLAGS})
target_include_directories(libstring PRIVATE ${CMAKE_SOURCE_DIR}/src)