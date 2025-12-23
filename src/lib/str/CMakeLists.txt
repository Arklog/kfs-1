add_library(libstring OBJECT
    KString.cpp
)
target_compile_options(libstring PRIVATE ${KERN_COMPILER_FLAGS})
target_include_directories(libstring PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_library(libstring64 STATIC
    KString.cpp
)
target_compile_options(libstring64 PRIVATE ${KERN_COMPILER_FLAGS} -O0)
target_include_directories(libstring64 PRIVATE ${CMAKE_SOURCE_DIR}/src)