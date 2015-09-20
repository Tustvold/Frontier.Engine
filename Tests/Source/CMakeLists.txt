add_subdirectory(Rendering)
add_subdirectory(Event)
add_subdirectory(Util)
add_subdirectory(Mock)

set (SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE)

set (HEADERS ${HEADERS}
    PARENT_SCOPE)