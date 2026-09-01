add_library(core INTERFACE)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(KFS::core ALIAS core)
add_library(KFS::core-test ALIAS core)