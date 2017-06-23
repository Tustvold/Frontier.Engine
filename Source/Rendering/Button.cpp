#include "Button.h"
#include <Engine.h>
#include <Event/EventManager.h>
#include "View.h"
#include <Event/Input/InputManager.h>

NS_FT_BEGIN

static Button* s_selected_button = nullptr;

void Button::setSelected() {
    if (s_selected_button == this)
        return;

    if (s_selected_button != nullptr) {
        s_selected_button->setDeselected();
    }

    s_selected_button = this;

    if (s_selected_button->getSelectDelegatesEnabled()) {
        s_selected_button->on_select_delegate_(s_selected_button);
    }
}

void Button::setDeselected() {
    if (s_selected_button != this)
        return;
    if (getSelectDelegatesEnabled())
        on_deselect_delegate_(this);
    s_selected_button = nullptr;
}

Button::Button(Node* renderer) :
        mouse_entered_(false), 
        flags_(UseSceneGraphPriority),
        node_(renderer) {
}

Button::~Button() {
    if (s_selected_button == this) {
        s_selected_button = nullptr;
    }

    if (getMouseDelegateAdded())
        Engine::getInputManager()->removeMouseDelegate(this);
    if (getEnterExitDelegatesEnabled()) {
        Engine::getEventManager()->unregisterDelegate<MouseEventDispatcher>(this, &Button::onMouseMove);
        Engine::getEventManager()->unregisterDelegate<MouseEventDispatcher>(this, &Button::mouseExitEvent);
    }
}

bool Button::onMouseDown(const MouseButtonPressedEvent& event) {
    if (event.mouse_button_ != GLFW_MOUSE_BUTTON_LEFT || !node_->containsMousePosition(event.cursor_pos_)) {
        setDeselected();
        return false;
    }

    mouse_pressed_delegate_(this, event);

    setSelected();
    return true;
}

void Button::onMouseDrag(const MouseMoveEvent& event, int mouse_button) {
    mouse_dragged_delegate_(this, event);
}

void Button::onMouseRelease(const MouseButtonReleasedEvent& event) {
    if (!node_->containsMousePosition(event.cursor_pos_))
        return;
    mouse_released_delegate_(this, event);
}

void Button::onMouseMove(const MouseMoveEvent& event) {
    if (!getMouseDelegateEnabled())
        return;
    auto contains = node_->containsMousePosition(event.cursor_pos_);
    if (contains == mouse_entered_)
        return;
    if (contains) {
        mouse_enter_delegate_(this);
    } else {
        mouse_exit_delegate_(this);
    }
    mouse_entered_ = contains;
}

uint32_t Button::getMouseDelegatePriority() const {
    if (!getUseSceneGraphPriority())
        return MouseDelegate::getMouseDelegatePriority();
    return node_->getDrawOrder() + FTBUTTON_BASE_NODE_PRIORITY;
}

bool Button::getMouseDelegateEnabled() const {
    if (getUseSceneGraphPriority() && node_->getDrawOrder() == NODE_DRAW_ORDER_INVALID)
        return false;
    if (mouse_input_enabled_delegate_.empty())
        return node_->getIsActive();
    return node_->getIsActive() && mouse_input_enabled_delegate_(this);
}

void Button::enableClickDelegates() {
    if (getClickDelegatesEnabled())
        return;
    flags_ |= ClickDelegatesEnabled;
    if (!getMouseDelegateAdded())
        Engine::getInputManager()->addMouseDelegate(this);
}

void Button::enableSelectDelegates() {
    if (getSelectDelegatesEnabled())
        return;
    flags_ |= SelectDelegatesEnabled;
    if (!getMouseDelegateAdded())
        Engine::getInputManager()->addMouseDelegate(this);
}

void Button::enableEnterExitDelegates() {
    if (getEnterExitDelegatesEnabled())
        return;
    flags_ |= EnterExitDelegatesEnabled;
    Engine::getEventManager()->registerDelegate<MouseEventDispatcher>(this, &Button::mouseExitEvent);
    Engine::getEventManager()->registerDelegate<MouseEventDispatcher>(this, &Button::onMouseMove);
}

void Button::mouseExitEvent(const MouseExitEvent& event) {
    if (!getMouseDelegateEnabled())
        return;
    if (mouse_entered_) {
        mouse_exit_delegate_(this);
        mouse_entered_ = false;
    }
}

NS_FT_END
