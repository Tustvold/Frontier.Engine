#pragma once
#include <Frontier.h>

struct FTWindowResizeEvent;
class FTEventManager;
class FTInputManager;
class FTDirector;
class FTFileManager;

class FTEngine {
public:
    static FTDirector* getDirector() {
        return getSharedInstance()->director_;
    }

    static FTInputManager* getInputManager() {
        return getSharedInstance()->input_manager_;
    }

    static FTEventManager* getEventManager() {
        return getSharedInstance()->event_manager_;
    }

    static FTFileManager* getFileManager() {
        return getSharedInstance()->file_manager_;
    }

    static bool cleanup();

    static bool setup(bool is_mocked = false);

    static void init();

    static int run() {
        return getSharedInstance()->_run();
    }

    static GLFWwindow* getWindow() {
        return getSharedInstance()->window_;
    }

    static const glm::tvec2<int>& getWindowSize() {
        return getSharedInstance()->window_size_;
    }

    static void setWindowsSize(const glm::tvec2<int>& size);

private:
    static FTEngine* getSharedInstance();

    FTEngine();
    ~FTEngine();

    bool _setup(bool is_mocked);

    int _run();

    void screensizeChanged(const FTWindowResizeEvent& event);

    FTEventManager* event_manager_;
    
    
    FTInputManager* input_manager_;
    FTDirector* director_;
    FTFileManager* file_manager_;

    GLFWwindow* window_;
    glm::tvec2<int> window_size_;

    bool setup_;
    double last_tick_time_;
    double fps_time_acc_;
    double time_left_after_ticks_;
    double update_timestep_;
};
