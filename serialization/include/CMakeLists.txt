include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HEADER_FILES
        array.h
        core.h
        meta.h
        object.h
        primitive.h
        root.h
        serialization.h
        )

set(SERIALIZATION_LIB_SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/serialization/src/array.cpp
        ${CMAKE_SOURCE_DIR}/serialization/src/core.cpp
        ${CMAKE_SOURCE_DIR}/serialization/src/main.cpp
        ${CMAKE_SOURCE_DIR}/serialization/src/object.cpp
        ${CMAKE_SOURCE_DIR}/serialization/src/primitive.cpp
        )

add_library(SerializationLib STATIC
        ${HEADER_FILES}
        ${SERIALIZATION_LIB_SOURCE_FILES}
        )

target_include_directories(SerializationLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(SerializationLib PROPERTIES LINKER_LANGUAGE CXX)
