#include "FTKeyboardEventDispatcher.h"
#include <Frontier.h>
#include <FTEngine.h>

static Gallant::Delegate5<GLFWwindow*, int, int, int, int> keyPressedEventDelegate;

FTKeyboardEventDispatcher::FTKeyboardEventDispatcher() {
    keyPressedEventDelegate.Bind(this, &FTKeyboardEventDispatcher::keyPressedEvent);
    auto window = FTEngine::getWindow();
    glfwSetKeyCallback(window, [](GLFWwindow* window_, int key_, int scancode_, int action_, int mods_) {
                           keyPressedEventDelegate(window_, key_, scancode_, action_, mods_);
                       });
}

FTKeyboardEventDispatcher::~FTKeyboardEventDispatcher() {

}

void FTKeyboardEventDispatcher::keyPressedEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        raiseEvent(FTKeyPressedEvent(key, scancode, mods));
    } else if (action == GLFW_RELEASE) {
        raiseEvent(FTKeyReleasedEvent(key, scancode, mods));
    }
}
