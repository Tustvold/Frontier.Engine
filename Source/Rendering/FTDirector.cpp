#include "FTDirector.h"

#include <Frontier.h>
#include <Event/Input/FTInputManager.h>

#include <Rendering/Shader/FTShaderCache.h>
#include <Rendering/Textures/FTTexture.h>
#include "Shader/FTVertexColorShaderProgram.h"
#include "Shader/FTVertexTextureShaderProgram.h"
#include "Shader/FTFontShader.h"
#include "Text/FTFontCache.h"
#include <sstream>
#include <FTEngine.h>
#include <Event/Engine/FTEngineEventDispatcher.h>
#include <Event/FTEventManager.h>
#include <Event/Window/FTWindowEventDispatcher.h>

class FTWindowEventDispatcher;

FTDirector::FTDirector() {
}


FTDirector::~FTDirector() {
    FTLOG("Director destroyed");
    scene_.reset();
}

int FTDirector::setup() {
    // Setup Graphics
    if (!glfwInit()) {
        FTLOG( "Failed to initialize GLFW\n");
        return -1;
    }

    window_size_ = glm::vec2(1024, 768);

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    // Open a window and create its OpenGL context
    window_ = glfwCreateWindow((int)window_size_.x, (int)window_size_.y, "FPS:", nullptr, nullptr);
    if (window_ == nullptr) {
        FTLogError("Failed to open GLFW window. Most likely your system doesn't support OpenGL version 3.3");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window_);

    //glfwSwapInterval(0);

    glewExperimental = true;

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    loadDefaultFonts();

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glEnable(GL_SCISSOR_TEST);

    //Setup Misc
    auto window_resize_delegate = Gallant::Delegate1<const FTWindowResizeEvent&>(this, &FTDirector::windowSizeChangeEvent);
    FTEngine::getEventManager()->getEventDispatcher<FTWindowEventDispatcher>()->registerDelegate(window_resize_delegate);

    return 0;
}

void FTDirector::loadDefaultFonts() {
    auto fontCache = FTEngine::getFontCache();

    fontCache->loadFont("Resources/Fonts/Vera.ttf");
}

void FTDirector::windowSizeChangeEvent(const FTWindowResizeEvent& event) {
    glViewport(0, 0, event.width_, event.height_);
}

int FTDirector::run() {

    double fps = 60;
    double fps_time_acc = 0;
    last_tick_time_ = glfwGetTime();
    FTPreDrawEvent pre_draw_event;
    auto engine_event_dispatcher = FTEngine::getEventManager()->getEventDispatcher<FTEngineEventDispatcher>();

    do {
        double current_time = glfwGetTime();
        double dt = (current_time - last_tick_time_);
        last_tick_time_ = current_time;
        if (dt > 0) {
            fps = 0.1f * fps + 0.9f / dt;
            fps_time_acc += dt;
        }

        if (fps_time_acc > 1.0f) {
            fps_time_acc -= 1.0f;

            std::ostringstream ss;
            ss << "FPS: " << fps;
            glfwSetWindowTitle(window_, ss.str().c_str());
        }

        pre_draw_event.delta_time_ = dt;
        pre_draw_event.average_fps_ = fps;
        engine_event_dispatcher->raiseEvent(pre_draw_event);

        glDisable(GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_SCISSOR_TEST);

        scene_->draw();

        // Swap buffers
        glfwSwapBuffers(window_);
        glfwPollEvents();
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window_, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window_) == 0);

    FTEngine::getShaderCache()->unloadAllShaders();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();


    return 0;
}
