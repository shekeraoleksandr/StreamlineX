cmake_minimum_required(VERSION 3.24)
project(StreamlineX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(serialization)
add_subdirectory(EventSystem)

add_executable(StreamlineX main.cpp)