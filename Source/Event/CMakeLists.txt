add_subdirectory(Engine)
add_subdirectory(Keyboard)
add_subdirectory(Mouse)
add_subdirectory(Window)
add_subdirectory(Input)

set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/EventManager.cpp
    PARENT_SCOPE)


set (HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/Event.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EventDispatcher.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EventManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/EventHelpers.h
    PARENT_SCOPE)
