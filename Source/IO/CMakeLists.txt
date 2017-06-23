add_subdirectory(Serialization)

set(SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/FileManager.cpp
        PARENT_SCOPE)

set(HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/FileManager.h
        PARENT_SCOPE)