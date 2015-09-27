add_subdirectory(Engine)
add_subdirectory(Keyboard)
add_subdirectory(Mouse)
add_subdirectory(Window)
add_subdirectory(Input)

set (SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/TestEventDispatcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestEventManager.cpp
PARENT_SCOPE)

set (HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/TestEventDispatcherTypes.h
PARENT_SCOPE)