#pragma once
#include "FTMouseEvents.h"
#include <Event/FTEventDispatcher.h>

struct GLFWwindow;

class FTMouseEventDispatcher : public FTEventDispatcher<FTMouseMoveEvent, FTMouseEnterEvent, FTMouseExitEvent> {
public:
    FTMouseEventDispatcher();
    ~FTMouseEventDispatcher();
private:
    void mouseMoveEvent(GLFWwindow* window, double x, double y);
    void mouseEnterEvent(GLFWwindow* window, int enter);
        
    bool has_last_mouse_pos_;
    double last_mouse_pos_x_;
    double last_mouse_pos_y_;
};