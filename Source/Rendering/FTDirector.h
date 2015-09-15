#pragma once

#include <ThirdParty/Signals/Signal.h>
#include "Scene/FTScene.h"
class FTCamera;
struct GLFWwindow;

// Class which manages drawing the world
// This class is not thread safe and should only be called from the OpenGL thread
class FTDirector {
    friend class FTEngine;
public:
    int run();

    Gallant::Signal1<float>* getPreDrawEventHandler() {
        return &pre_draw_event_handler_;
    }

    glm::vec2 getWindowSize() {
        return window_size_;
    }

    Gallant::Signal2<float, float>* getWindowSizeChangeEventHandler() {
        return &window_size_change_event_handler_;
    }

    void setCurrentScene(std::shared_ptr<FTScene>& scene) {
        scene_ = scene;
    }

private:
    FTDirector();
    ~FTDirector();

    int setup();

    void loadDefaultFonts();

    void windowSizeChange(GLFWwindow* window, int width, int height);

    static void windowSizeChangeCallback(GLFWwindow* window, int width, int height);

    std::shared_ptr<FTScene> scene_;
    GLFWwindow* window_;
    glm::vec2 window_size_;

    double last_tick_time_;

    Gallant::Signal1<float> pre_draw_event_handler_;
    Gallant::Signal2<float, float> window_size_change_event_handler_;
};
