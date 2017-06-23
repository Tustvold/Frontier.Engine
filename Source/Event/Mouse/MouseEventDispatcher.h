#pragma once
#include "Frontier.h"
#include "MouseEvents.h"
#include <Event/EventDispatcher.h>

struct GLFWwindow;

NS_FT_BEGIN

class MouseEventDispatcher : public EventDispatcher<MouseMoveEvent, MouseEnterEvent, MouseExitEvent, MouseButtonPressedEvent, MouseButtonReleasedEvent, MouseScrollEvent> {
public:
    MouseEventDispatcher();
    ~MouseEventDispatcher();
private:
    void mouseMoveEvent(GLFWwindow* window, double x, double y);
    void mouseEnterEvent(GLFWwindow* window, int enter);
    void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) const;
    void mouseScrollEvent(GLFWwindow* window, double scroll_x, double scroll_y) const;

    bool has_last_mouse_pos_;
    glm::vec2 last_mouse_pos_;
};

NS_FT_END