add_library(include INTERFACE)
target_include_directories(include INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(KFS::include ALIAS include)
add_library(KFS::include-test ALIAS include)