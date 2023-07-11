set(SOURCE_FILES
        array.cpp
        core.cpp
        main.cpp
        object.cpp
        primitive.cpp
        )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(serializationSrc
        ${SOURCE_FILES}
        )

target_link_libraries(serializationSrc
        PRIVATE
        SerializationLib)

