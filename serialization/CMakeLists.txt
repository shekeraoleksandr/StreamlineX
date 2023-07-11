cmake_minimum_required(VERSION 3.20)

project(serialization)

option(BUILD_TESTS "Build unit tests (default OFF)" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(include)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()