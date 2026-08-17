function (create_test_and_nontest)
    set(options)
    set(oneValueArgs NAME)
    set(multipleValueArgs FILE_SRCS LIBRARIES INCLUDE_DIR INCLUDE_DIR_PRIVATE)

    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multipleValueArgs}" ${ARGN})

    set(LIB_NAME ${ARG_NAME})
    set(LIB_SRCS ${ARG_FILE_SRCS})
    set(LIB_LIBRARIES ${ARG_LIBRARIES})
    set(LIB_INCLUDE_DIR ${ARG_INCLUDE_DIR})
    set(LIB_INCLUDE_DIR_PRIVATE ${ARG_INCLUDE_DIR_PRIVATE})

    set(LIBTEST_NAME "${ARG_NAME}-test")
    set(LIBTEST_SRCS ${ARG_FILE_SRCS})
    list(TRANSFORM ARG_LIBRARIES APPEND "-test" OUTPUT_VARIABLE LIBTEST_LIBRARIES)
    set(LIBTEST_INCLUDE_DIR ${ARG_INCLUDE_DIR})
    set(LIBTEST_INCLUDE_DIR_PRIVATE ${ARG_INCLUDE_DIR_PRIVATE})

    add_library(${LIB_NAME} STATIC ${LIB_SRCS})
    target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDE_DIR} PRIVATE ${LIB_INCLUDE_DIR_PRIVATE})
    target_link_libraries(${LIB_NAME} PUBLIC ${LIB_LIBRARIES})
    target_compile_options(${LIB_NAME} PRIVATE ${KFLAGS})
    set_target_properties(${LIB_NAME} PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})

    add_library(${LIBTEST_NAME} STATIC ${LIBTEST_SRCS})
    target_include_directories(${LIBTEST_NAME} PUBLIC ${LIBTEST_INCLUDE_DIR} PRIVATE ${LIBTEST_INCLUDE_DIR_PRIVATE})
    target_link_libraries(${LIBTEST_NAME} PUBLIC ${LIBTEST_LIBRARIES})
    target_compile_options(${LIBTEST_NAME} PRIVATE ${KFLAGS})
    target_compile_definitions(${LIBTEST_NAME} PRIVATE KFS_HOST_TEST)
    set_target_properties(${LIBTEST_NAME} PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})
endfunction()

add_subdirectory(core)
add_subdirectory(drivers)
add_subdirectory(include)
add_subdirectory(lib)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
enable_language(ASM_NASM)
add_library(bootloader OBJECT bootloader.nasm)
set_source_files_properties(bootloader.nasm PROPERTIES LANGUAGE ASM_NASM)
target_compile_options(bootloader PRIVATE
    $<$<COMPILE_LANGUAGE:ASM_NASM>: -f elf32>
)

add_executable(kernel_bonus
        main.cpp
)
target_include_directories(kernel_bonus PRIVATE .)
target_link_libraries(kernel_bonus PRIVATE
        bootloader
        KFS::Drivers::vga
        KFS::Lib::container
        KFS::Lib::format
        KFS::Lib::logging
        KFS::Lib::port
        KFS::Lib::string
        libkbd
)
target_compile_options(kernel_bonus PRIVATE ${KFLAGS})
target_compile_definitions(kernel_bonus PUBLIC KEYBOARD_ENABLE)
target_link_options(kernel_bonus PRIVATE -T${CMAKE_SOURCE_DIR}/src/linker.ld -m32 ${KFLAGS})
set_target_properties(kernel_bonus PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})

add_executable(kernel
        main.cpp
)
target_include_directories(kernel PRIVATE .)
target_link_libraries(kernel PRIVATE
        bootloader
        KFS::Lib::port
        KFS::Drivers::vga
        KFS::Lib::string
        libkbd_disabled
        KFS::Lib::logging
        KFS::Lib::format
)
target_compile_options(kernel PRIVATE ${KFLAGS})
target_link_options(kernel PRIVATE -T${CMAKE_SOURCE_DIR}/src/linker.ld -m32 ${KFLAGS})
set_target_properties(kernel PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})