
# This is a static library so that it can provide the definitions for the glew functions which are
# declared as belonging to a static library
add_library(glfwmock STATIC glfwmock.cpp glfwmock.h)

target_link_libraries(glfwmock
    glewmock
)

target_include_directories(glfwmock PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../glfw/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../glewmock/
)