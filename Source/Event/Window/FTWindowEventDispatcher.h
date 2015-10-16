#pragma once
#include "FTWindowEvents.h"
#include <Event/FTEventDispatcher.h>

struct GLFWwindow;

class FTWindowEventDispatcher : public FTEventDispatcher<FTWindowResizeEvent> {
public:
    FTWindowEventDispatcher();
    virtual ~FTWindowEventDispatcher();
private:
    void windowResizeEvent(GLFWwindow* window, int width, int height);
};
