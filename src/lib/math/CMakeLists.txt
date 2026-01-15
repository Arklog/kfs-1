add_library(math OBJECT math.cpp)
target_include_directories(math PRIVATE ${CMAKE_SOURCE_DIR}/src .)
target_compile_options(math PRIVATE ${KFLAGS})
set_target_properties(math PROPERTIES CMAKE_CXX_COMPILER ${CXX_CROSS_COMPILER})