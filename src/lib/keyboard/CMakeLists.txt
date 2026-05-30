add_library(libkbd STATIC
        keyboardHandler.hpp
        keyboardHandler.cpp
)
target_include_directories(libkbd PRIVATE . ${CMAKE_SOURCE_DIR}/src)
target_compile_options(libkbd PRIVATE ${KFLAGS})
target_compile_definitions(libkbd PUBLIC KEYBOARD_ENABLE)
target_link_libraries(libkbd PUBLIC libport logging)
set_target_properties(libkbd PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})

add_library(libkbd_disabled STATIC
        keyboardHandler.hpp
        keyboardHandler.cpp
)
target_include_directories(libkbd_disabled PRIVATE . ${CMAKE_SOURCE_DIR}/src)
target_compile_options(libkbd_disabled PRIVATE ${KFLAGS})
target_link_libraries(libkbd_disabled PUBLIC libport logging)
set_target_properties(libkbd_disabled PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})