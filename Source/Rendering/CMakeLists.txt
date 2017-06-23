add_subdirectory(Camera)
add_subdirectory(Mesh)
add_subdirectory(Primitives)
add_subdirectory(Shader)
add_subdirectory(Text)
add_subdirectory(Texture)
add_subdirectory(Transform)
add_subdirectory(Action)
add_subdirectory(BoundingShape)
add_subdirectory(Lighting)
add_subdirectory(Material)

set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/Director.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ShaderNode.cpp
        PARENT_SCOPE)

set(HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Director.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Drawable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/DrawableNode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Node.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Scene.h
        ${CMAKE_CURRENT_SOURCE_DIR}/View.h
        ${CMAKE_CURRENT_SOURCE_DIR}/LayoutNode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ShaderNode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/WindowSizeNode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Button.h
        PARENT_SCOPE)
