add_subdirectory(arch)
add_subdirectory(lib)

add_library(kernel STATIC
        main.cpp
)
target_include_directories(kernel PRIVATE .)
target_link_libraries(kernel PRIVATE libport libvga libstring libkbd logging format)
target_compile_options(kernel PRIVATE ${KFLAGS})
