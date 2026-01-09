enable_testing()
add_executable(test_vga
        vga.cpp
        VGAMonitor.cpp
)

target_link_libraries(test_vga
        PRIVATE
        libport
        libvga
        Catch2::Catch2WithMain
        libstring
)
target_include_directories(
        test_vga
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)
target_compile_options(test_vga PRIVATE -m32)

catch_discover_tests(test_vga)

