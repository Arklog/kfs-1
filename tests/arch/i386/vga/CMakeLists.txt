add_executable(test_vga
        vga.cpp
)
target_link_libraries(test_vga
        PRIVATE
        libvga
        Catch2::Catch2WithMain
        libstring
)
target_include_directories(
        test_vga
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

catch_discover_tests(test_vga)