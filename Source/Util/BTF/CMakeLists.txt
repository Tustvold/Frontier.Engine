
set (SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/Buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CompressionBuffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Tag.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TagBase.cpp
    PARENT_SCOPE)

set (HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Buffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CompressionBuffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Tag.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TagBase.h
    PARENT_SCOPE)
