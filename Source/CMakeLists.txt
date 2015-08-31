
add_subdirectory(Rendering)
add_subdirectory(ThirdParty)
add_subdirectory(Util)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/FTObject.cpp
    PARENT_SCOPE)


set (HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Frontier.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTCircularBuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTEngine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTObject.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTPtr.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTString.h
    ${CMAKE_CURRENT_SOURCE_DIR}/FTTimer.h
    PARENT_SCOPE)
