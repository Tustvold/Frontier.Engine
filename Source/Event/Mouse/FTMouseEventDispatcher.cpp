#include "FTMouseEventDispatcher.h"
#include <Frontier.h>
#include <Rendering/FTDirector.h>

static Gallant::Delegate3<GLFWwindow*, double, double> mouse_move_event_delegate;
static Gallant::Delegate2<GLFWwindow*, int> mouse_enter_event_delegate;

FTMouseEventDispatcher::FTMouseEventDispatcher() : has_last_mouse_pos_(false) {
    mouse_move_event_delegate.Bind(this, &FTMouseEventDispatcher::mouseMoveEvent);
    mouse_enter_event_delegate.Bind(this, &FTMouseEventDispatcher::mouseEnterEvent);
    auto window = FTEngine::getDirector()->getWindow();
    glfwSetCursorPosCallback(window, [](GLFWwindow* window_, double x, double y)
    {
        mouse_move_event_delegate(window_, x, y);
    });
    glfwSetCursorEnterCallback(window, [](GLFWwindow* window_, int enter)
    {
        mouse_enter_event_delegate(window_, enter);
    });
}

FTMouseEventDispatcher::~FTMouseEventDispatcher() {
}

void FTMouseEventDispatcher::mouseMoveEvent(GLFWwindow* window, double x, double y) {
    double delta_x = 0;
    double delta_y = 0;
    if (has_last_mouse_pos_) {
        delta_x = x - last_mouse_pos_x_;
        delta_y = y - last_mouse_pos_y_;
    }
    raiseEvent(FTMouseMoveEvent(x, y, delta_x, delta_y));
    last_mouse_pos_x_ = x;
    last_mouse_pos_y_ = y;
    has_last_mouse_pos_ = true;
}

void FTMouseEventDispatcher::mouseEnterEvent(GLFWwindow* window, int enter) {
    if (enter == GL_TRUE) {
        raiseEvent(FTMouseEnterEvent());
    } else if (enter == GL_FALSE) {
        raiseEvent(FTMouseExitEvent());
    }
    // We purge last position data as the delta is meaningless if the mouse has exited and then re-entered the window
    has_last_mouse_pos_ = false;
}