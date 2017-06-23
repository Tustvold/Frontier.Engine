#include "Engine.h"

#include "Rendering/Director.h"
#include "Event/Input/InputManager.h"
#include "Rendering/Shader/ShaderCache.h"
#include "Rendering/Text/FontCache.h"
#include "IO/FileManager.h"
#include "Event/Engine/EngineEventDispatcher.h"
#include <sstream>

NS_FT_BEGIN

static Engine* s_instance = nullptr;

Engine* Engine::getSharedInstance() {
    FTAssert(s_instance != nullptr, "Please call Engine::setup() first");
    return s_instance;
}

Engine::Engine() : window_(nullptr), window_size_(1024, 768), setup_(false), last_tick_time_(0), fps_time_acc_(0), time_left_after_ticks_(0), update_timestep_(1/30.0) {
    event_manager_ = new EventManager();
    input_manager_ = new InputManager();
    file_manager_ = new FileManager();
    director_ = new Director();
}

Engine::~Engine() {
    director_->cleanup();

    delete director_;
    delete file_manager_;
    delete input_manager_;
    delete event_manager_;
}

bool Engine::_setup(bool no_window, bool is_mocked) {
    if (!no_window) {

        FTAssert(glfwInit(), "Failed to initialize GLFW\n");

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

        // Open a window and create its OpenGL context
        window_ = glfwCreateWindow((int)window_size_.x, (int)window_size_.y, "FPS:", nullptr, nullptr);
        FTAssert(window_ != nullptr, "Failed to open GLFW window. Most likely your system doesn't support OpenGL version 3.1");
        
        glfwMakeContextCurrent(window_);

        glfwSwapInterval(1);

        glewExperimental = true;

        // Initialize GLEW
        FTAssert(glewInit() == GLEW_OK, "Failed to initialize GLEW\n");
        
        // Dark blue background
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    }

    if (!no_window || is_mocked) {
        input_manager_->setup();

        getEventManager()->registerDelegate<WindowEventDispatcher>(this, &Engine::screensizeChanged);
    }

    file_manager_->setup();

    director_->setup();

    return true;
}

void Engine::setWindowsSize(const glm::tvec2<int>& size) {
    auto window = s_instance->window_;
    glfwSetWindowSize(window, size.x, size.y);
}


bool Engine::setup(bool no_window, bool is_mocked) {
    if (s_instance == nullptr) {
        init();
    }
    FTAssert(!s_instance->setup_, "Engine already setup");
    if (s_instance->_setup(no_window, is_mocked)) {
        return true;
    }
    cleanup();
    return false;
}

void Engine::init() {
    FTAssert(s_instance == nullptr, "Engine::init() already called");
    s_instance = new Engine();
}

int Engine::_run() {
    double fps = 60;
    last_tick_time_ = glfwGetTime();
    time_left_after_ticks_ = 0;
    UpdateEvent update_event;
    DrawEvent draw_event;
    PreTickEvent pre_tick_event;
    auto engine_event_dispatcher = Engine::getEventManager()->getEventDispatcher<EngineEventDispatcher>();

    do {
        double current_time = glfwGetTime();
        double dt = (current_time - last_tick_time_);
        last_tick_time_ = current_time;
        if (dt > 0) {
            fps = 0.1f * fps + 0.9f / dt;
            fps_time_acc_ += dt;
        }

        if (fps_time_acc_ > 1.0) {
            std::ostringstream ss;
            ss << "FPS: " << fps;
            glfwSetWindowTitle(window_, ss.str().c_str());
            fps_time_acc_ -= 1.0;
        }

        time_left_after_ticks_ += dt;


        engine_event_dispatcher->raiseEvent(pre_tick_event);

        // We cap the remaining time at 5 timesteps
        // This is to reduce impact on the frame rate.
        // If we are this far behind, slowing down the simulation is acceptable
        //
        // This will also ignore situations where the program's execution is 
        // paused, for example, by a breakpoint
        if (time_left_after_ticks_ > update_timestep_*5.0) {
            FTLogWarn("Simulation running more than 5 timesteps behind");
            time_left_after_ticks_ = update_timestep_*5.0;
        }
        
        while (time_left_after_ticks_ >= update_timestep_) {
            update_event.delta_time_ = update_timestep_;
            engine_event_dispatcher->raiseEvent(update_event);
            time_left_after_ticks_ -= update_timestep_;
        }

        
        draw_event.delta_time_ = dt;
        draw_event.average_fps_ = fps;
        draw_event.window_ = window_;
        engine_event_dispatcher->raiseEvent(draw_event);

        getInputManager()->sortDelegates();
        
        glfwPollEvents();
        
    } // TODO: Change this to use input manager and window event manager
    while (glfwGetKey(window_, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
    glfwWindowShouldClose(window_) == 0);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

void Engine::screensizeChanged(const WindowResizeEvent& event) {
    window_size_.x = event.width_;
    window_size_.y = event.height_;
}

bool Engine::cleanup() {
    if (s_instance == nullptr)
        return true;
    delete s_instance;
    s_instance = nullptr;
    return true;
}

NS_FT_END
