#include "FTEngine.h"

#include "Rendering/FTDirector.h"
#include "Event/Input/FTInputManager.h"
#include "Rendering/Shader/FTShaderCache.h"
#include "Rendering/Text/FTFontCache.h"
#include "Event/FTEventManager.h"
#include "Util/FTFileManager.h"
#include "Rendering/Action/FTActionManager.h"
#include "Event/Engine/FTEngineEventDispatcher.h"
#include <sstream>
#include "Event/Window/FTWindowEventDispatcher.h"

static FTEngine* s_instance = nullptr;

FTEngine* FTEngine::getSharedInstance() {
    FTAssert(s_instance != nullptr, "Please call FTEngine::setup() first");
    return s_instance;
}

FTEngine::FTEngine() : window_(nullptr), window_size_(1024, 768), setup_(false), last_tick_time_(0), fps_time_acc_(0), time_left_after_ticks_(0), update_timestep_(1/30.0) {
    event_manager_ = new FTEventManager();
    input_manager_ = new FTInputManager();
    file_manager_ = new FTFileManager();
    director_ = new FTDirector();
}

FTEngine::~FTEngine() {
    director_->cleanup();

    delete director_;
    delete file_manager_;
    delete input_manager_;
    delete event_manager_;
}

bool FTEngine::_setup(bool no_window, bool is_mocked) {
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

        getEventManager()->registerDelegate<FTWindowEventDispatcher>(this, &FTEngine::screensizeChanged);
    }

    file_manager_->setup();

    director_->setup();

    return true;
}

void FTEngine::setWindowsSize(const glm::tvec2<int>& size) {
    auto window = s_instance->window_;
    glfwSetWindowSize(window, size.x, size.y);
}


bool FTEngine::setup(bool no_window, bool is_mocked) {
    if (s_instance == nullptr) {
        init();
    }
    FTAssert(!s_instance->setup_, "FTEngine already setup");
    if (s_instance->_setup(no_window, is_mocked)) {
        return true;
    }
    cleanup();
    return false;
}

void FTEngine::init() {
    FTAssert(s_instance == nullptr, "FTEngine::init() already called");
    s_instance = new FTEngine();
}

int FTEngine::_run() {
    double fps = 60;
    last_tick_time_ = glfwGetTime();
    time_left_after_ticks_ = 0;
    FTUpdateEvent update_event;
    FTDrawEvent draw_event;
    FTPreTickEvent pre_tick_event;
    auto engine_event_dispatcher = FTEngine::getEventManager()->getEventDispatcher<FTEngineEventDispatcher>();

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

void FTEngine::screensizeChanged(const FTWindowResizeEvent& event) {
    window_size_.x = event.width_;
    window_size_.y = event.height_;
}

bool FTEngine::cleanup() {
    if (s_instance == nullptr)
        return true;
    delete s_instance;
    s_instance = nullptr;
    return true;
}
