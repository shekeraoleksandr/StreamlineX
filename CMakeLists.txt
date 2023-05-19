cmake_minimum_required(VERSION 3.24)
project(StreamlineX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_custom_target(lineX)
ADD_DEPENDENCIES(lineX  serialization EventSystem)

add_subdirectory(serialization)
add_subdirectory(EventSystem)


