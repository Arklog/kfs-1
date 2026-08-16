create_test_and_nontest(
        NAME libvga
        FILE_SRCS
        vga.cpp
        VGAMonitor.cpp
        VGAMonitor.hpp
        VGACursor.cpp
        VGACursor.hpp
        VGADisplay.cpp
        VGADisplay.hpp
        ScrollbackBuffer.cpp
        ScrollbackBuffer.hpp
        INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src
        LIBRARIES container math logging libport
)

add_subdirectory(tests)