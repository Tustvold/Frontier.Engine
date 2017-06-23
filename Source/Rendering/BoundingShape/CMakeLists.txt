set (SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/BoundingShape.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BoundingEllipsoid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BoundingCuboid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/BoundingShapeWrapper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CompoundBoundingShape.cpp
    
   PARENT_SCOPE)

set (HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/BoundingShape.h
        ${CMAKE_CURRENT_SOURCE_DIR}/BoundingEllipsoid.h
        ${CMAKE_CURRENT_SOURCE_DIR}/BoundingCuboid.h
        ${CMAKE_CURRENT_SOURCE_DIR}/BoundingShapeWrapper.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CompoundBoundingShape.h
    PARENT_SCOPE)
