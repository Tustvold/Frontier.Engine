set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/FontTexture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TextureDDS.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MutableTexture.cpp
        PARENT_SCOPE)

set(HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/FontTexture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Texture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TextureDDS.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MutableTexture.h
        PARENT_SCOPE)
