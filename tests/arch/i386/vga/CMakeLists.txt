add_executable(test_vga
        vga.cpp
        VGAMonitor.cpp
)

target_compile_definitions(libvga PRIVATE KFS_HOST_TESTS)

target_link_libraries(test_vga
        PRIVATE
        Catch2::Catch2WithMain
        libvga
        libstring
)
target_include_directories(
        test_vga
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)
target_compile_options(test_vga PRIVATE -m32)

catch_discover_tests(test_vga)