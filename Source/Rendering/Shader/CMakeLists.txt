set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/FontShader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ShaderCache.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexColorShaderProgram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexShaderProgram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexTextureShaderProgram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CircleShaderProgram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CircleBorderShaderProgram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexShaderProgramColor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexShaderProgramLighting.cpp
        PARENT_SCOPE)

set(HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/FontShader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ShaderCache.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexColorShaderProgram.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexShaderProgram.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexTextureShaderProgram.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CircleShaderProgram.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CircleBorderShaderProgram.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexShaderProgramColor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/VertexShaderProgramLighting.h
        PARENT_SCOPE)
