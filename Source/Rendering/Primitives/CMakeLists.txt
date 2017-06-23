set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/Cube.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Plane.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TexturedPlane.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CircleSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CircleBorderSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Line.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Polygon.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Cuboid.cpp
        PARENT_SCOPE)

set(HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Cube.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Plane.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TexturedPlane.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CircleSprite.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CircleBorderSprite.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Line.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Polygon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Cuboid.h

        PARENT_SCOPE)
