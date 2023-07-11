set(SOURCE_FILES
        window.cpp
        main.cpp
        )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(OpenGL REQUIRED)

add_executable(eventSrc
        ${SOURCE_FILES}
        )

target_link_libraries(eventSrc
        PRIVATE
        EventLib
        OpenGL::GL
        CONAN_PKG::glfw
        )