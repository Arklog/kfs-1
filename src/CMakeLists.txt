add_subdirectory(arch)
add_subdirectory(lib)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
enable_language(ASM_NASM)
add_library(bootloader OBJECT bootloader.s)
set_source_files_properties(bootloader.s PROPERTIES LANGUAGE ASM_NASM)
target_compile_options(bootloader PRIVATE
    $<$<COMPILE_LANGUAGE:ASM_NASM>: -f elf32>
)

add_executable(kernel
        main.cpp
)
target_include_directories(kernel PRIVATE .)
target_link_libraries(kernel PRIVATE bootloader libport libvga libstring libkbd logging format)
target_compile_options(kernel PRIVATE ${KFLAGS})
target_link_options(kernel PRIVATE -T${CMAKE_SOURCE_DIR}/src/linker.ld -m32 ${KFLAGS})
set_target_properties(kernel PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})