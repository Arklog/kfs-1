add_library(libkbd OBJECT
        keyboardHandler.hpp
        keyboardHandler.cpp
)
target_include_directories(libkbd PRIVATE . ${CMAKE_SOURCE_DIR}/src)
target_compile_options(libkbd PRIVATE ${KFLAGS})