add_library(libvga OBJECT
        vga.cpp
        VGAMonitor.cpp
        VGAMonitor.hpp
        VGACursor.cpp
        VGACursor.hpp
        VGAStreamModifier.cpp
        VGAStreamModifier.hpp
)
target_include_directories(libvga PRIVATE . ${CMAKE_SOURCE_DIR}/src)
target_compile_options(libvga PRIVATE ${KERN_COMPILER_FLAGS})

add_library(libvga64 STATIC
    vga.cpp
    VGAMonitor.cpp
    VGAMonitor.hpp
    VGACursor.cpp
    VGACursor.hpp
    VGAStreamModifier.cpp
    VGAStreamModifier.hpp
)
target_include_directories(libvga64 PRIVATE . ${CMAKE_SOURCE_DIR}/src)
target_compile_options(libvga64 PRIVATE ${KERN_COMPILER_FLAGS} -m64)