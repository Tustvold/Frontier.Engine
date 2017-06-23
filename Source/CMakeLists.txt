
add_subdirectory(Rendering)
add_subdirectory(ThirdParty)
add_subdirectory(Util)
add_subdirectory(Event)

set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine.cpp
    PARENT_SCOPE)


set (HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Frontier.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine.h
    PARENT_SCOPE)
