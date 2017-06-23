set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/FTCube.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FTPlane.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FTTexturedPlane.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FTCircleSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FTCircleBorderSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FTLine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FTPolygon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FTCuboid.cpp
        PARENT_SCOPE)

set(HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/FTCube.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTPlane.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTTexturedPlane.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTCircleSprite.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTCircleBorderSprite.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTLine.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTPolygon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTCuboid.h

        PARENT_SCOPE)
