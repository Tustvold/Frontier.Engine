add_subdirectory(Serialization)

set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/FTLog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FileManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StringUtils.cpp
        PARENT_SCOPE)

set(HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Rect.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Math.h
        ${CMAKE_CURRENT_SOURCE_DIR}/StringUtils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Timer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FTLog.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FileManager.h
        PARENT_SCOPE)