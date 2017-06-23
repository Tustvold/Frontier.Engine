#include "MouseEventDispatcher.h"
#include <Frontier.h>
#include <Engine.h>

NS_FT_BEGIN

static Gallant::Delegate3<GLFWwindow*, double, double> mouse_move_event_delegate;
static Gallant::Delegate2<GLFWwindow*, int> mouse_enter_event_delegate;
static Gallant::Delegate4<GLFWwindow*, int, int, int> mouse_button_event_delegate;
static Gallant::Delegate3<GLFWwindow*, double, double> mouse_scroll_event_delegate;

MouseEventDispatcher::MouseEventDispatcher() : has_last_mouse_pos_(false), last_mouse_pos_(-1) {
    mouse_move_event_delegate.Bind(this, &MouseEventDispatcher::mouseMoveEvent);
    mouse_enter_event_delegate.Bind(this, &MouseEventDispatcher::mouseEnterEvent);
    mouse_button_event_delegate.Bind(this, &MouseEventDispatcher::mouseButtonEvent);
    mouse_scroll_event_delegate.Bind(this, &MouseEventDispatcher::mouseScrollEvent);
    auto window = Engine::getWindow();
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

MouseEventDispatcher::~MouseEventDispatcher() {
}

void MouseEventDispatcher::mouseMoveEvent(GLFWwindow* window, double x, double y) {
    // Convert window coordinates to normal coords - (0,0) in the bottom left
    y = Engine::getWindowSize().y - y;
    auto pos = glm::vec2((float)x, (float)y);

    glm::vec2 delta;
    if (has_last_mouse_pos_) {
        delta = pos - last_mouse_pos_;
    }
    raiseEvent(MouseMoveEvent(pos, delta));
    last_mouse_pos_ = pos;
    has_last_mouse_pos_ = true;
}

void MouseEventDispatcher::mouseEnterEvent(GLFWwindow* window, int enter) {
    if (enter == GL_TRUE) {
        raiseEvent(MouseEnterEvent());
    } else if (enter == GL_FALSE) {
        raiseEvent(MouseExitEvent());
    }
    // We purge last position data as the delta is meaningless if the mouse has exited and then re-entered the window
    has_last_mouse_pos_ = false;
    last_mouse_pos_ = glm::vec2(-1);
}

void MouseEventDispatcher::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) const {
    // We assume that if we haven't received position data that the mouse is outside the window.
    if (action == GLFW_PRESS) {
        raiseEvent(MouseButtonPressedEvent(last_mouse_pos_, button, !has_last_mouse_pos_));
    } else if (action == GLFW_RELEASE) {
        raiseEvent(MouseButtonReleasedEvent(last_mouse_pos_, button, !has_last_mouse_pos_));
    }
}

void MouseEventDispatcher::mouseScrollEvent(GLFWwindow* window, double scroll_x, double scroll_y) const {
    // We assume that if we haven't received position data that the mouse is outside the window.
    auto scroll = glm::vec2((float)scroll_x, (float)scroll_y);
    raiseEvent(MouseScrollEvent(last_mouse_pos_, scroll, !has_last_mouse_pos_));
}

NS_FT_END
