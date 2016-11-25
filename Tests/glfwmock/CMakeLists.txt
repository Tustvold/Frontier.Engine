# This is a static library so that it can provide the definitions for the glew functions which are
# declared as belonging to a static library
add_library(glfwmock STATIC glfwmock.cpp glfwmock.h)

target_link_libraries(glfwmock
        ${FRONTIER_ENGINE_TEST_LIBS}
        gmock
)

target_include_directories(glfwmock PUBLIC
        ${FRONTIER_ENGINE_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}
)