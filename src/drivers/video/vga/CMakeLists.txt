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
        LIBRARIES
            container
            math
            libport
            logging
)

add_subdirectory(tests)