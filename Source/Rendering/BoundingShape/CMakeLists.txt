set (SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/FTBoundingShape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTBoundingEllipsoid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTBoundingCuboid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTBoundingShapeWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FTCompoundBoundingShape.cpp
    
   PARENT_SCOPE)

set (HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/FTBoundingShape.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTBoundingEllipsoid.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTBoundingCuboid.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTBoundingShapeWrapper.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTCompoundBoundingShape.h
    PARENT_SCOPE)
