add_subdirectory(arch)
add_subdirectory(lib)

add_library(kernel STATIC
        main.cpp
        arch/i386/keyboard/keyboardHandler.cpp
        arch/i386/keyboard/keyboardHandler.hpp
)
target_include_directories(kernel PRIVATE .)
target_link_libraries(kernel PRIVATE libvga libstring)
target_compile_options(kernel PRIVATE ${KERN_COMPILER_FLAGS})