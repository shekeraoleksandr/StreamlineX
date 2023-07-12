set(SOURCE_FILES
        src/main.cpp
        src/client.cpp
        )

set(HEADER_FILES
        src/client.h
        )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(clientSrc
        ${SOURCE_FILES}
        ${HEADER_FILES}
        )

target_link_libraries(clientSrc
        PRIVATE
        SerializationLib
        )

target_include_directories(clientSrc PRIVATE ${CMAKE_SOURCE_DIR}/serialization/include)