#pragma once
#include "FTKeyboardEvents.h"
#include <Event/FTEventDispatcher.h>

struct GLFWwindow;

class FTKeyboardEventDispatcher : public FTEventDispatcher<FTKeyPressedEvent, FTKeyReleasedEvent> {
public:
    FTKeyboardEventDispatcher();
    ~FTKeyboardEventDispatcher();
private:
    void keyPressedEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
};