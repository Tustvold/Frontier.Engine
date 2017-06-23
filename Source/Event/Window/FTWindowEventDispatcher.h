#pragma once
#include "FTWindowEvents.h"
#include <Event/FTEventDispatcher.h>

struct GLFWwindow;

NS_FT_BEGIN

class FTWindowEventDispatcher : public FTEventDispatcher<FTWindowResizeEvent> {
public:
    FTWindowEventDispatcher();
    virtual ~FTWindowEventDispatcher();
private:
    void windowResizeEvent(GLFWwindow* window, int width, int height);
};

NS_FT_END