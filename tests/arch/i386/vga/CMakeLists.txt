enable_testing()
add_executable(test_vga
    VGACursor.cpp
)
target_include_directories(test_vga PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_vga PRIVATE Catch2::Catch2WithMain libvga64)
