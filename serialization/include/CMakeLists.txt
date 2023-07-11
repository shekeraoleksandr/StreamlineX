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

add_library(SerializationLib STATIC
        ${HEADER_FILES}
        )

set_target_properties(SerializationLib PROPERTIES LINKER_LANGUAGE CXX)
