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
        ${CMAKE_CURRENT_SOURCE_DIR}/FTDirector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FTNode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FTButton.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FTShaderNode.cpp
        PARENT_SCOPE)

set(HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/FTDirector.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTDrawable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTDrawableNode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTNode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTScene.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTView.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTLayoutNode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTShaderNode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTWindowSizeNode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTButton.h
        PARENT_SCOPE)
