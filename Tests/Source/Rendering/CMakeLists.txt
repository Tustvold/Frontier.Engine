
add_subdirectory(Scene)
add_subdirectory(Camera)
add_subdirectory(Mesh)

set (SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/TestDirector.cpp
PARENT_SCOPE)

set (HEADERS ${HEADERS}
PARENT_SCOPE)