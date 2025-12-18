add_library(libvga OBJECT
        vga.cpp
        VGAMonitor.cpp
        VGAMonitor.hpp
)
target_include_directories(libvga PRIVATE . ${CMAKE_SOURCE_DIR}/src)
target_compile_options(libvga PRIVATE ${KERN_COMPILER_FLAGS})