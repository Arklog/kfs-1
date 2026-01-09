add_subdirectory(arch)
add_subdirectory(lib)

add_library(kernel STATIC
        main.cpp
)
target_include_directories(kernel PRIVATE .)
target_link_libraries(kernel PRIVATE libvga libstring libkbd)
target_compile_options(kernel PRIVATE ${KERN_COMPILER_FLAGS})