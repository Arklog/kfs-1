create_test_and_nontest(
        NAME libkbd
        FILE_SRCS
            keyboardHandler.cpp
            keyboardHandler.hpp
        INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src
        LIBRARIES libport logging
)

target_compile_definitions(libkbd PRIVATE KEYBOARD_ENABLE)

create_test_and_nontest(
        NAME libkbd_disabled
        FILE_SRCS
        keyboardHandler.cpp
        keyboardHandler.hpp
        INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src
        LIBRARIES libport logging
)