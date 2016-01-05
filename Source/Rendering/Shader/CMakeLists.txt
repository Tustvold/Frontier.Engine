set (SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/FTFontShader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTShaderCache.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTVertexColorShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTVertexShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTVertexTextureShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTCircleShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTCircleBorderShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTVertexShaderProgramColor.cpp
    PARENT_SCOPE)

set (HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/FTFontShader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTShaderCache.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTShaderProgram.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTVertexColorShaderProgram.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTVertexShaderProgram.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTVertexTextureShaderProgram.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTCircleShaderProgram.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTCircleBorderShaderProgram.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTVertexShaderProgramColor.h
    PARENT_SCOPE)
