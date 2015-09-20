#pragma once

#include <ThirdParty/Signals/Signal.h>
#include "Scene/FTScene.h"
#include <Event/Engine/FTEngineEventDispatcher.h>
struct FTWindowResizeEvent;
class FTCamera;
struct GLFWwindow;

// Class which manages drawing the world
// This class is not thread safe and should only be called from the OpenGL thread
class FTDirector {
    friend class FTEngine;
public:
    int run();

    glm::vec2 getWindowSize() {
        return window_size_;
    }

    void setCurrentScene(std::shared_ptr<FTScene>& scene) {
        scene_ = scene;
    }

    GLFWwindow* getWindow() const {
        return window_;
    };

    void draw();

private:
    FTDirector();
    ~FTDirector();

    int setup();

    void loadDefaultFonts();

    void windowSizeChangeEvent(const FTWindowResizeEvent& event);

    std::shared_ptr<FTScene> scene_;
    GLFWwindow* window_;
    glm::vec2 window_size_;

    double last_tick_time_;
};
