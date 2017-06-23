#pragma once
#include "KeyboardEvents.h"
#include <Event/EventDispatcher.h>
#include <Frontier.h>

struct GLFWwindow;

NS_FT_BEGIN

class KeyboardEventDispatcher : public EventDispatcher<KeyPressedEvent, KeyReleasedEvent, KeyRepeatEvent, CharInputEvent> {
public:
    KeyboardEventDispatcher();
    ~KeyboardEventDispatcher();
private:
    void keyPressedEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    void charEvent(GLFWwindow* window, unsigned int character, int mods);
};

NS_FT_END