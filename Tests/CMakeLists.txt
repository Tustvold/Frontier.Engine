enable_testing()

SET(SOURCES )
SET(HEADERS )

add_subdirectory(Source)

# We can use GLOB here as in order for a CMakeList to be used a pre-existing one
# must have been modified and therefore the build system will know to rebuild
FILE(GLOB_RECURSE CMAKELISTS Source/*CMakeLists.txt)

add_executable(Frontier.Engine.Tests ${SOURCES} ${HEADERS} ${CMAKELISTS})
target_include_directories(Frontier.Engine.Tests PUBLIC
    ../ThirdParty/googletest/googletest/include)

# Rebuild directory structure within Visual Studio
foreach(FILE ${SOURCES} ${HEADERS} ${CMAKELISTS})
	get_filename_component(PARENT_DIR "${FILE}" PATH)

	string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" GROUP "${PARENT_DIR}")
	string(REPLACE "/" "\\" GROUP "${GROUP}")

	source_group("${GROUP}" FILES "${FILE}")
endforeach()

	
target_link_libraries(Frontier.Engine.Tests
    gtest
    Frontier.Engine
)
	

# Move back into Frontier.Engine directory within Visual Studio
set_target_properties(Frontier.Engine.Tests PROPERTIES FOLDER Frontier.Engine)
