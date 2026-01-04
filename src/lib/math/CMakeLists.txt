add_library(math OBJECT math.cpp)
target_include_directories(math PRIVATE ${CMAKE_SOURCE_DIR}/src .)
target_compile_options(math PRIVATE ${KERN_COMPILER_FLAGS})
