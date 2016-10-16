enable_testing()

SET(SOURCES)
SET(HEADERS)

add_subdirectory(glfwmock)
add_subdirectory(Source)

add_executable(Frontier.Engine.Tests ${SOURCES} ${HEADERS})

target_include_directories(Frontier.Engine.Tests PUBLIC
        Source)


target_link_libraries(Frontier.Engine.Tests
        ${FRONTIER_ENGINE_TEST_LIBS}
        glfwmock
)


add_custom_command(TARGET Frontier.Engine.Tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestResources)
