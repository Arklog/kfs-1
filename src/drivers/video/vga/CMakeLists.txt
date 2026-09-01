create_test_and_nontest(
        NAME vga
        FILE_SRCS
            src/vga.cpp
            src/VGAMonitor.cpp
            src/VGACursor.cpp
            src/VGADisplay.cpp
            src/ScrollbackBuffer.cpp
        INCLUDE_DIR
            include
        LIBRARIES
            KFS::include
            KFS::Lib::container
            KFS::Lib::logging
            KFS::Lib::math
            KFS::Lib::port
)

# Theses alias are required in order to clion to provide autocompletion for them
add_library(KFS::Drivers::vga ALIAS vga)
add_library(KFS::Drivers::vga-test ALIAS vga-test)

add_subdirectory(tests)