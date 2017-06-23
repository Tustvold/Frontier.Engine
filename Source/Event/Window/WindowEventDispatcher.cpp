#include "WindowEventDispatcher.h"
#include <Frontier.h>
#include <Engine.h>

NS_FT_BEGIN

static Gallant::Delegate3<GLFWwindow*, int, int> window_resize_delegate;

WindowEventDispatcher::WindowEventDispatcher() {
    window_resize_delegate.Bind(this, &WindowEventDispatcher::windowResizeEvent);
    auto window = Engine::getWindow();
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window_, int width, int height) {
                                  window_resize_delegate(window_, width, height);
                              });
}

WindowEventDispatcher::~WindowEventDispatcher() {
}

void WindowEventDispatcher::windowResizeEvent(GLFWwindow* window, int width, int height) {
    raiseEvent(WindowResizeEvent(width, height));
}

NS_FT_END