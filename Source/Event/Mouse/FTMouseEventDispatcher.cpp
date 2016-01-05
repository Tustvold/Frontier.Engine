#include "FTMouseEventDispatcher.h"
#include <Frontier.h>
#include <FTEngine.h>

static Gallant::Delegate3<GLFWwindow*, double, double> mouse_move_event_delegate;
static Gallant::Delegate2<GLFWwindow*, int> mouse_enter_event_delegate;
static Gallant::Delegate4<GLFWwindow*, int, int, int> mouse_button_event_delegate;
static Gallant::Delegate3<GLFWwindow*, double, double> mouse_scroll_event_delegate;

FTMouseEventDispatcher::FTMouseEventDispatcher() : has_last_mouse_pos_(false), last_mouse_pos_x_(-1), last_mouse_pos_y_(-1) {
    mouse_move_event_delegate.Bind(this, &FTMouseEventDispatcher::mouseMoveEvent);
    mouse_enter_event_delegate.Bind(this, &FTMouseEventDispatcher::mouseEnterEvent);
    mouse_button_event_delegate.Bind(this, &FTMouseEventDispatcher::mouseButtonEvent);
    mouse_scroll_event_delegate.Bind(this, &FTMouseEventDispatcher::mouseScrollEvent);
    auto window = FTEngine::getWindow();
    glfwSetCursorPosCallback(window, [](GLFWwindow* window_, double x, double y) {
                                 mouse_move_event_delegate(window_, x, y);
                             });
    glfwSetCursorEnterCallback(window, [](GLFWwindow* window_, int enter) {
                                   mouse_enter_event_delegate(window_, enter);
                               });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window_, int button, int action, int mods) {
                                   mouse_button_event_delegate(window_, button, action, mods);
                               });
    glfwSetScrollCallback(window, [](GLFWwindow* window_, double scroll_x, double scroll_y) {
        mouse_scroll_event_delegate(window_, scroll_x, scroll_y);
    });
}

FTMouseEventDispatcher::~FTMouseEventDispatcher() {
}

void FTMouseEventDispatcher::mouseMoveEvent(GLFWwindow* window, double x, double y) {
    // Convert window coordinates to normal coords - (0,0) in the bottom left
    y = FTEngine::getWindowSize().y - y;

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
    last_mouse_pos_x_ = -1 ;
    last_mouse_pos_y_ = -1 ;
}

void FTMouseEventDispatcher::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) const {
    // We assume that if we haven't received position data that the mouse is outside the window.
    if (action == GLFW_PRESS) {
        raiseEvent(FTMouseButtonPressedEvent(last_mouse_pos_x_, last_mouse_pos_y_, button, !has_last_mouse_pos_));
    } else if (action == GLFW_RELEASE) {
        raiseEvent(FTMouseButtonReleasedEvent(last_mouse_pos_x_, last_mouse_pos_y_, button, !has_last_mouse_pos_));
    }
}

void FTMouseEventDispatcher::mouseScrollEvent(GLFWwindow* window, double scroll_x, double scroll_y) const {
    // We assume that if we haven't received position data that the mouse is outside the window.
    raiseEvent(FTMouseScrollEvent(last_mouse_pos_x_, last_mouse_pos_y_, scroll_x, scroll_y, !has_last_mouse_pos_));
}
