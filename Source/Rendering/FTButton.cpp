#include "FTButton.h"
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include "FTView.h"
#include <Event/Input/FTInputManager.h>

static FTButton* s_selected_button = nullptr;

void FTButton::setSelected() {
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

void FTButton::setDeselected() {
    if (s_selected_button != this)
        return;
    if (getSelectDelegatesEnabled())
        on_deselect_delegate_(this);
    s_selected_button = nullptr;
}

FTButton::FTButton(FTNode* renderer) :
        mouse_entered_(false), 
        flags_(UseSceneGraphPriority),
        node_(renderer) {
}

FTButton::~FTButton() {
    if (s_selected_button == this) {
        s_selected_button = nullptr;
    }

    if (getMouseDelegateAdded())
        FTEngine::getInputManager()->removeMouseDelegate(this);
    if (getEnterExitDelegatesEnabled()) {
        FTEngine::getEventManager()->unregisterDelegate<FTMouseEventDispatcher>(this, &FTButton::onMouseMove);
        FTEngine::getEventManager()->unregisterDelegate<FTMouseEventDispatcher>(this, &FTButton::mouseExitEvent);
    }
}

bool FTButton::onMouseDown(const FTMouseButtonPressedEvent& event) {
    if (event.mouse_button_ != GLFW_MOUSE_BUTTON_LEFT || !node_->containsMousePosition(event.cursor_pos_)) {
        setDeselected();
        return false;
    }

    bool ret = true;

    mouse_pressed_delegate_(this, event);

    setSelected();
    return true;
}

void FTButton::onMouseDrag(const FTMouseMoveEvent& event, int mouse_button) {
    mouse_dragged_delegate_(this, event);
}

void FTButton::onMouseRelease(const FTMouseButtonReleasedEvent& event) {
    if (!node_->containsMousePosition(event.cursor_pos_))
        return;
    mouse_released_delegate_(this, event);
}

void FTButton::onMouseMove(const FTMouseMoveEvent& event) {
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

uint32_t FTButton::getMouseDelegatePriority() const {
    if (!getUseSceneGraphPriority())
        return FTMouseDelegate::getMouseDelegatePriority();
    return node_->getDrawOrder() + FTBUTTON_BASE_NODE_PRIORITY;
}

bool FTButton::getMouseDelegateEnabled() const {
    if (getUseSceneGraphPriority() && node_->getDrawOrder() == NODE_DRAW_ORDER_INVALID)
        return false;
    if (mouse_input_enabled_delegate_.empty())
        return node_->getIsActive();
    return node_->getIsActive() && mouse_input_enabled_delegate_(this);
}

void FTButton::enableClickDelegates() {
    if (getClickDelegatesEnabled())
        return;
    flags_ |= ClickDelegatesEnabled;
    if (!getMouseDelegateAdded())
        FTEngine::getInputManager()->addMouseDelegate(this);
}

void FTButton::enableSelectDelegates() {
    if (getSelectDelegatesEnabled())
        return;
    flags_ |= SelectDelegatesEnabled;
    if (!getMouseDelegateAdded())
        FTEngine::getInputManager()->addMouseDelegate(this);
}

void FTButton::enableEnterExitDelegates() {
    if (getEnterExitDelegatesEnabled())
        return;
    flags_ |= EnterExitDelegatesEnabled;
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTButton::mouseExitEvent);
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTButton::onMouseMove);
}

void FTButton::mouseExitEvent(const FTMouseExitEvent& event) {
    if (!getMouseDelegateEnabled())
        return;
    if (mouse_entered_) {
        mouse_exit_delegate_(this);
        mouse_entered_ = false;
    }
}

