#pragma once
#include <Frontier.h>

NS_FT_BEGIN

struct WindowResizeEvent;
class EventManager;
class InputManager;
class Director;
class FileManager;

class Engine {
public:
    static Director* getDirector() {
        return getSharedInstance()->director_;
    }

    static InputManager* getInputManager() {
        return getSharedInstance()->input_manager_;
    }

    static EventManager* getEventManager() {
        return getSharedInstance()->event_manager_;
    }

    static FileManager* getFileManager() {
        return getSharedInstance()->file_manager_;
    }

    static bool cleanup();

    static bool setup(bool no_window = false, bool is_mocked = false);

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
    static Engine* getSharedInstance();

    Engine();
    ~Engine();

    bool _setup(bool no_window, bool is_mocked);

    int _run();

    void screensizeChanged(const WindowResizeEvent& event);

    EventManager* event_manager_;
    
    
    InputManager* input_manager_;
    Director* director_;
    FileManager* file_manager_;

    GLFWwindow* window_;
    glm::tvec2<int> window_size_;

    bool setup_;
    double last_tick_time_;
    double fps_time_acc_;
    double time_left_after_ticks_;
    double update_timestep_;
};

NS_FT_END