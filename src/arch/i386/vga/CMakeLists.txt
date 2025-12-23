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
target_compile_options(libvga PRIVATE ${KFLAGS})

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
target_compile_options(libvga64 PRIVATE ${KFLAGS})