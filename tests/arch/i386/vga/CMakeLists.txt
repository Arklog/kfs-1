enable_testing()
add_executable(test_vga
        vga.cpp
        VGAMonitor.cpp
)
target_compile_definitions(libvga64 PRIVATE KFS_HOST_TESTS)
target_include_directories(test_vga PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_vga PRIVATE Catch2::Catch2WithMain libvga64 libstring)
catch_discover_tests(test_vga)
