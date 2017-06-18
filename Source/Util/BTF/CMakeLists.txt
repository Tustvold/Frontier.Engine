
set (SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/Buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CompressionBuffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Tag.cpp
        PARENT_SCOPE)

set (HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Buffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CompressionBuffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Tag.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Serialization.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TagID.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TTag.h
    PARENT_SCOPE)
