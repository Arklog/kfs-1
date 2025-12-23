add_library(libstring OBJECT
        KString.cpp
)
target_compile_options(libstring PRIVATE ${KFLAGS})
target_include_directories(libstring PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_library(libstring64 STATIC
        KString.cpp
)
target_compile_options(libstring64 PRIVATE ${KFLAGS} -O0)
target_include_directories(libstring64 PRIVATE ${CMAKE_SOURCE_DIR}/src)