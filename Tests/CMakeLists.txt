enable_testing()

SET(SOURCES )
SET(HEADERS )

add_subdirectory(Source)

# We can use GLOB here as in order for a CMakeList to be used a pre-existing one
# must have been modified and therefore the build system will know to rebuild
FILE(GLOB_RECURSE CMAKELISTS Source/*CMakeLists.txt)

add_executable(Frontier.Engine.Tests ${SOURCES} ${HEADERS} ${CMAKELISTS})
target_include_directories(Frontier.Engine.Tests PUBLIC
    ../ThirdParty/glmock/glfwmock/
    Source)

# Rebuild directory structure within Visual Studio
foreach(FILE ${SOURCES} ${HEADERS} ${CMAKELISTS})
	get_filename_component(PARENT_DIR "${FILE}" PATH)

	string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" GROUP "${PARENT_DIR}")
	string(REPLACE "/" "\\" GROUP "${GROUP}")

	source_group("${GROUP}" FILES "${FILE}")
endforeach()

	
target_link_libraries(Frontier.Engine.Tests
    glfwmock
    freetype
    freetype-gl
    Frontier.Engine
)
	

# Move back into Frontier.Engine directory within Visual Studio
set_target_properties(Frontier.Engine.Tests PROPERTIES FOLDER Frontier.Engine)

add_custom_command(TARGET Frontier.Engine.Tests POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_CURRENT_BINARY_DIR}/Resources)

install(TARGETS Frontier.Engine.Tests
     RUNTIME DESTINATION bin)