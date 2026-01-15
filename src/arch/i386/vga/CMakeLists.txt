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
set_target_properties(libvga PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})

add_library(libvga_test OBJECT $<TARGET_OBJECTS:libvga>)
target_compile_options(libvga_test PRIVATE KFS_HOST_TESTS)