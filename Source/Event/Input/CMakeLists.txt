set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/InputManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MouseDelegate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/KeyboardDelegate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/KeyMapping.cpp
    PARENT_SCOPE)


set (HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/InputManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MouseDelegate.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KeyboardDelegate.h
        ${CMAKE_CURRENT_SOURCE_DIR}/KeyMapping.h
    PARENT_SCOPE)
