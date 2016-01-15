#include "FTKeyboardEventDispatcher.h"
#include <Frontier.h>
#include <FTEngine.h>

static Gallant::Delegate5<GLFWwindow*, int, int, int, int> keyPressedEventDelegate;
static Gallant::Delegate3<GLFWwindow*, unsigned int, int> charInputDelegate;

FTKeyboardEventDispatcher::FTKeyboardEventDispatcher() {
    keyPressedEventDelegate.Bind(this, &FTKeyboardEventDispatcher::keyPressedEvent);
    charInputDelegate.Bind(this, &FTKeyboardEventDispatcher::charEvent);
    auto window = FTEngine::getWindow();

    glfwSetKeyCallback(window, [](GLFWwindow* window_, int key_, int scancode_, int action_, int mods_) {
                           keyPressedEventDelegate(window_, key_, scancode_, action_, mods_);
                       });

    glfwSetCharModsCallback(window, [](GLFWwindow* window_, unsigned int character_, int mods_) {
        charInputDelegate(window_, character_, mods_);
    });
}

FTKeyboardEventDispatcher::~FTKeyboardEventDispatcher() {

}

void FTKeyboardEventDispatcher::keyPressedEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        raiseEvent(FTKeyPressedEvent(key, scancode, mods));
    } else if (action == GLFW_RELEASE) {
        raiseEvent(FTKeyReleasedEvent(key, scancode, mods));
    } else if (action == GLFW_REPEAT) {
        raiseEvent(FTKeyRepeatEvent(key, scancode, mods));
    }
}

void FTKeyboardEventDispatcher::charEvent(GLFWwindow* window, unsigned int character, int mods) {
    FTAssert(character <= WCHAR_MAX, "Character out of bounds of wchar");
    wchar_t converted_char = (wchar_t)character;
    raiseEvent(FTCharInputEvent(converted_char, mods));
}
