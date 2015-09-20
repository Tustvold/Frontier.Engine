#include "FTWindowEventDispatcher.h"
#include <Frontier.h>
#include <FTEngine.h>
#include <Rendering/FTDirector.h>

static Gallant::Delegate3<GLFWwindow*, int, int> window_resize_delegate;

FTWindowEventDispatcher::FTWindowEventDispatcher() {
    window_resize_delegate.Bind(this, &FTWindowEventDispatcher::windowResizeEvent);
    auto window = FTEngine::getDirector()->getWindow();
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window_, int width, int height)
    {
        window_resize_delegate(window_, width, height);
    });
}

FTWindowEventDispatcher::~FTWindowEventDispatcher() {
}

void FTWindowEventDispatcher::windowResizeEvent(GLFWwindow* window, int width, int height) {
    raiseEvent(FTWindowResizeEvent(width, height));
}