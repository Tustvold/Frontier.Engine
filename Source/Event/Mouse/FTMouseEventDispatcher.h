#pragma once
#include "FTMouseEvents.h"
#include <Event/FTEventDispatcher.h>

struct GLFWwindow;

class FTMouseEventDispatcher : public FTEventDispatcher<FTMouseMoveEvent, FTMouseEnterEvent, FTMouseExitEvent, FTMouseButtonPressedEvent, FTMouseButtonReleasedEvent> {
public:
    FTMouseEventDispatcher();
    ~FTMouseEventDispatcher();
private:
    void mouseMoveEvent(GLFWwindow* window, double x, double y);
    void mouseEnterEvent(GLFWwindow* window, int enter);
    void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
        
    bool has_last_mouse_pos_;
    double last_mouse_pos_x_;
    double last_mouse_pos_y_;
};