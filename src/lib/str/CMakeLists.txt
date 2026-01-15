add_library(libstring OBJECT
        KString.cpp
)
target_compile_options(libstring PRIVATE ${KFLAGS})
target_include_directories(libstring PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(libstring PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})