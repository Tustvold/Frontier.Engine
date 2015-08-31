add_subdirectory(Camera)
add_subdirectory(Mesh)
add_subdirectory(Primitives)
add_subdirectory(Scene)
add_subdirectory(Shader)
add_subdirectory(Text)
add_subdirectory(Textures)

set (SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/FTDirector.cpp
    PARENT_SCOPE)

set (HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/FTDirector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTDrawable.h
    PARENT_SCOPE)
