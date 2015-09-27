add_subdirectory(Engine)
add_subdirectory(Keyboard)
add_subdirectory(Mouse)
add_subdirectory(Window)
add_subdirectory(Input)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/FTEventManager.cpp
    PARENT_SCOPE)


set (HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/FTEvent.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTEventDispatcher.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTEventManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTEventHelpers.h
    PARENT_SCOPE)
