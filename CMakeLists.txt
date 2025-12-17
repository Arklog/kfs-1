cmake_minimum_required(VERSION 3.5)
project(kfs-1)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)

add_executable(kfs-1 src/main.cpp)