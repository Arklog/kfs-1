add_library(format OBJECT
    format.cpp
)
target_compile_options(format PRIVATE ${KERN_COMPILER_FLAGS})
target_include_directories(format PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_library(format64 STATIC
    format.cpp
)
target_compile_options(format64 PRIVATE ${KERN_COMPILER_FLAGS} -O0)
target_include_directories(format64 PUBLIC ${CMAKE_SOURCE_DIR}/src)