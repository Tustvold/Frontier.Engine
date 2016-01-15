#pragma once
#include "Frontier.h"
#include "FTMouseEvents.h"
#include <Event/FTEventDispatcher.h>

struct GLFWwindow;

class FTMouseEventDispatcher : public FTEventDispatcher<FTMouseMoveEvent, FTMouseEnterEvent, FTMouseExitEvent, FTMouseButtonPressedEvent, FTMouseButtonReleasedEvent, FTMouseScrollEvent> {
public:
    FTMouseEventDispatcher();
    ~FTMouseEventDispatcher();
private:
    void mouseMoveEvent(GLFWwindow* window, double x, double y);
    void mouseEnterEvent(GLFWwindow* window, int enter);
    void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) const;
    void mouseScrollEvent(GLFWwindow* window, double scroll_x, double scroll_y) const;

    bool has_last_mouse_pos_;
    glm::vec2 last_mouse_pos_;
};
