enable_testing()
add_executable(test_format
    format.cpp
)
target_include_directories(test_format PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_format PRIVATE Catch2::Catch2WithMain format64 libstring64)