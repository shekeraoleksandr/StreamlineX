set(SOURCE_FILES
        src/main.cpp
        src/server.cpp
        )

set(HEADER_FILES
        src/server.h
        )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(serverSrc
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )

target_link_libraries(serverSrc
        PRIVATE
        SerializationLib
        )

target_include_directories(serverSrc PRIVATE ${CMAKE_SOURCE_DIR}/serialization/include)
