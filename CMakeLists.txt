cmake_minimum_required(VERSION 3.20)
project(StreamlineX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.14/conan.cmake"
            "conan.cmake")
endif()

include(conan.cmake)
conan_cmake_run(REQUIRES
        glfw/3.3.8
        BASIC_SETUP CMAKE_TARGETS
        GENERATORS cmake_find_package cmake_paths
        BUILD missing
        )

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_subdirectory(serialization)
add_subdirectory(EventSystem)


