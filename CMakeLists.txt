cmake_minimum_required(VERSION 3.5)
project(kfs-1)

set(CMAKE_CXX_STANDARD 23)

##################################
# Install external dependencies
##################################

include(FetchContent)

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.11.0
)

FetchContent_MakeAvailable(
        catch2
)

##################################
# Main source code
##################################

add_subdirectory(src)

add_executable(kfs-1 src/main.cpp)

##################################
# Tests
##################################

enable_testing()
add_subdirectory(tests)