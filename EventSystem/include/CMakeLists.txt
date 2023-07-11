include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(OpenGL REQUIRED)

set(HEADER_FILES
        event.h
        keyboard.h
        mouseevent.h
        window.h
        windowevent.h
        )

add_library(EventLib STATIC
        ${HEADER_FILES}
        )

set_target_properties(EventLib PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(EventLib
        OpenGL::GL
        CONAN_PKG::glfw
        )