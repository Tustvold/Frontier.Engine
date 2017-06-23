#pragma once
#include "WindowEvents.h"
#include <Event/EventDispatcher.h>

struct GLFWwindow;

NS_FT_BEGIN

class WindowEventDispatcher : public EventDispatcher<WindowResizeEvent> {
public:
    WindowEventDispatcher();
    virtual ~WindowEventDispatcher();
private:
    void windowResizeEvent(GLFWwindow* window, int width, int height);
};

NS_FT_END