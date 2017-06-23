set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/Font.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FontCache.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Label.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/InputLabel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/FontUtils.cpp
    PARENT_SCOPE)

set(HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Font.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FontCache.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Label.h
        ${CMAKE_CURRENT_SOURCE_DIR}/InputLabel.h
        ${CMAKE_CURRENT_SOURCE_DIR}/FontUtils.h
    PARENT_SCOPE)
