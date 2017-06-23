#include "FTWindowEventDispatcher.h"
#include <Frontier.h>
#include <FTEngine.h>

NS_FT_BEGIN

static Gallant::Delegate3<GLFWwindow*, int, int> window_resize_delegate;

FTWindowEventDispatcher::FTWindowEventDispatcher() {
    window_resize_delegate.Bind(this, &FTWindowEventDispatcher::windowResizeEvent);
    auto window = FTEngine::getWindow();
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window_, int width, int height) {
                                  window_resize_delegate(window_, width, height);
                              });
}

FTWindowEventDispatcher::~FTWindowEventDispatcher() {
}

void FTWindowEventDispatcher::windowResizeEvent(GLFWwindow* window, int width, int height) {
    raiseEvent(FTWindowResizeEvent(width, height));
}

NS_FT_END