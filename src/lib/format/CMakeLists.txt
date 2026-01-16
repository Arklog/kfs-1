add_library(format STATIC
        format.cpp
)
target_compile_options(format PRIVATE ${KFLAGS})
target_include_directories(format PUBLIC ${CMAKE_SOURCE_DIR}/src)
set_target_properties(format PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})