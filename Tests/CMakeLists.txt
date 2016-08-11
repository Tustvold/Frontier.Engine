enable_testing()

SET(SOURCES)
SET(HEADERS)

add_subdirectory(Source)

add_executable(Frontier.Engine.Tests ${SOURCES} ${HEADERS})
target_include_directories(Frontier.Engine.Tests PUBLIC
        ../ThirdParty/glmock/glfwmock/
        Source)
		
FILE(GLOB_RECURSE CMAKELISTS Source/*CMakeLists.txt)

# Rebuild directory structure within Visual Studio
foreach (FILE ${SOURCES} ${HEADERS} ${CMAKELISTS})
    get_filename_component(PARENT_DIR "${FILE}" PATH)

    string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    source_group("${GROUP}" FILES "${FILE}")
endforeach ()


target_link_libraries(Frontier.Engine.Tests
        Frontier.Engine
        freetype-gl
        freetype
        glfwmock
        glewmock
        glmock
        )


# Move back into Frontier.Engine directory within Visual Studio
get_target_property(FRONTIER_DIR Frontier.Engine FOLDER)
set_target_properties(Frontier.Engine.Tests PROPERTIES FOLDER ${FRONTIER_DIR})
target_compile_features(Frontier.Engine.Tests PRIVATE cxx_static_assert
        cxx_auto_type)

# MSVC by default runs programs with project's directory as the working directory
# So we need to copy resources there also
if (MSVC)
    add_custom_command(TARGET Frontier.Engine.Tests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_CURRENT_BINARY_DIR}/TestResources)
endif ()

add_custom_command(TARGET Frontier.Engine.Tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestResources)
