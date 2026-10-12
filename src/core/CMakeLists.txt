add_library(core STATIC
    gdt/gdt.cpp
)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(core PUBLIC KFS::include)

add_library(KFS::core ALIAS core)
add_library(KFS::core-test ALIAS core)