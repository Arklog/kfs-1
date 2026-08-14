add_executable(test_vga
        vga.cpp
        VGAMonitor.cpp
        ScrollbackBuffer.cpp
)

target_link_libraries(test_vga
        PRIVATE
        libvga-test
        Catch2::Catch2WithMain
)
target_include_directories(
        test_vga
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)
target_compile_options(test_vga PRIVATE -m32)
target_compile_definitions(test_vga PRIVATE KFS_HOST_TEST)

catch_discover_tests(test_vga)