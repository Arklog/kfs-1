add_library(libvga OBJECT
        vga.cpp
        VGAMonitor.cpp
        VGAMonitor.hpp
        VGACursor.cpp
        VGACursor.hpp
        VGADisplay.cpp
        VGADisplay.hpp
        ScrollbackBuffer.cpp
        ScrollbackBuffer.hpp
)
target_include_directories(libvga PRIVATE . ${CMAKE_SOURCE_DIR}/src)
target_compile_options(libvga PRIVATE ${KFLAGS})
target_link_libraries(libvga PUBLIC container math)
