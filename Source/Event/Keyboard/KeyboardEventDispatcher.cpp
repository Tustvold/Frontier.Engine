#include "KeyboardEventDispatcher.h"
#include <Frontier.h>
#include <Engine.h>

NS_FT_BEGIN

static Gallant::Delegate5<GLFWwindow*, int, int, int, int> keyPressedEventDelegate;
static Gallant::Delegate3<GLFWwindow*, unsigned int, int> charInputDelegate;

KeyboardEventDispatcher::KeyboardEventDispatcher() {
    keyPressedEventDelegate.Bind(this, &KeyboardEventDispatcher::keyPressedEvent);
    charInputDelegate.Bind(this, &KeyboardEventDispatcher::charEvent);
    auto window = Engine::getWindow();

    glfwSetKeyCallback(window, [](GLFWwindow* window_, int key_, int scancode_, int action_, int mods_) {
                           keyPressedEventDelegate(window_, key_, scancode_, action_, mods_);
                       });

    glfwSetCharModsCallback(window, [](GLFWwindow* window_, unsigned int character_, int mods_) {
        charInputDelegate(window_, character_, mods_);
    });
}

KeyboardEventDispatcher::~KeyboardEventDispatcher() {

}

void KeyboardEventDispatcher::keyPressedEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        raiseEvent(KeyPressedEvent(key, scancode, mods));
    } else if (action == GLFW_RELEASE) {
        raiseEvent(KeyReleasedEvent(key, scancode, mods));
    } else if (action == GLFW_REPEAT) {
        raiseEvent(KeyRepeatEvent(key, scancode, mods));
    }
}

void KeyboardEventDispatcher::charEvent(GLFWwindow* window, unsigned int character, int mods) {
    FTAssert(character <= WCHAR_MAX, "Character out of bounds of wchar");
    wchar_t converted_char = (wchar_t)character;
    raiseEvent(CharInputEvent(converted_char, mods));
}

NS_FT_END