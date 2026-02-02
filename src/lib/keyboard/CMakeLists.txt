add_library(libkbd STATIC
        keyboardHandler.hpp
        keyboardHandler.cpp
)
target_include_directories(libkbd PRIVATE . ${CMAKE_SOURCE_DIR}/src)
target_compile_options(libkbd PRIVATE ${KFLAGS})
target_link_libraries(libkbd PUBLIC libport logging)
set_target_properties(libkbd PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})