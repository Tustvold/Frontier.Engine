#pragma once
#include <Event/Input/MouseDelegate.h>
// When using scene graph priority, the delegate's priority is determined by adding this number to the draw_order of the node
#define FTBUTTON_BASE_NODE_PRIORITY 256

NS_FT_BEGIN

class Node;
// Wraps around an Node and performs intersection tests based on its bounding shape
// Exposes four delgates:
// mouse_enter - invoked when the mouse hovers over the button
// mouse_exit - invoked when the mouse leaves the area above the button
// mouse_pressed - invoked when the left mouse button is pressed whilst hovering above the button (invoked after mouse_enter)
// mouse_released - invoked when the left mouse button is released whilst the cursor is above the button having also been pressed whilst the cursor was above the button
class Button : public MouseDelegate {

public:
    enum Flags {
        ClickDelegatesEnabled = 1,
        SelectDelegatesEnabled = 1 << 1,
        EnterExitDelegatesEnabled = 1 << 2,
        UseSceneGraphPriority = 1 << 3
    };


    explicit Button(Node* renderer);
    
    virtual ~Button();

    bool onMouseDown(const MouseButtonPressedEvent& event) override;
    void onMouseDrag(const MouseMoveEvent&, int mouse_button) override;
    void onMouseRelease(const MouseButtonReleasedEvent& event) override;
    
    
    void onMouseMove(const MouseMoveEvent& event);

    void setMouseDelegatePriority(uint32_t priority) override {
        setUseSceneGraphPriority(false);
        MouseDelegate::setMouseDelegatePriority(priority);
    }

    uint32_t getMouseDelegatePriority() const override;

    template <class X, class Y>
    void bindMouseEnterDelegate(Y* pthis, void(X::* function_to_bind)(Button*)) {
        enableEnterExitDelegates();
        mouse_enter_delegate_.Connect(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMouseExitDelegate(Y* pthis, void(X::* function_to_bind)(Button*)) {
        enableEnterExitDelegates();
        mouse_exit_delegate_.Connect(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMousePressedDelegate(Y* pthis, void(X::* function_to_bind)(Button*, const MouseButtonPressedEvent&)) {
        enableClickDelegates();
        mouse_pressed_delegate_.Connect(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMouseDragDelegate(Y* pthis, void(X::* function_to_bind)(Button*, const MouseMoveEvent&)) {
        enableClickDelegates();
        mouse_dragged_delegate_.Connect(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMouseReleasedDelegate(Y* pthis, void(X::* function_to_bind)(Button*, const MouseButtonReleasedEvent&)) {
        enableClickDelegates();
        mouse_released_delegate_.Connect(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindOnSelectDelegate(Y* pthis, void(X::* function_to_bind)(Button*)) {
        enableSelectDelegates();
        on_select_delegate_.Connect(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindOnDeselectDelegate(Y* pthis, void(X::* function_to_bind)(Button*)) {
        enableSelectDelegates();
        on_deselect_delegate_.Connect(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindEnabledDelegate(Y* pthis, bool(X::* function_to_bind)(const Button*)) {
        mouse_input_enabled_delegate_.Bind(pthis, function_to_bind);
    }

    bool getMouseDelegateEnabled() const override;

    Node* getNode() const {
        return node_;
    }

    bool getClickDelegatesEnabled() const {
        return (flags_ & ClickDelegatesEnabled) != 0;
    }

    bool getSelectDelegatesEnabled() const {
        return (flags_ & SelectDelegatesEnabled) != 0;
    }

    bool getEnterExitDelegatesEnabled() const {
        return (flags_ & EnterExitDelegatesEnabled) != 0;
    }

    bool getUseSceneGraphPriority() const {
        return (flags_ & UseSceneGraphPriority) != 0;
    }

    void setUseSceneGraphPriority(bool enabled) {
        if (enabled)
            flags_ |= UseSceneGraphPriority;
        else
            flags_ &= ~UseSceneGraphPriority;
    }

    void enableClickDelegates();

    void enableSelectDelegates();

    void enableEnterExitDelegates();

    void setSelected();

    void setDeselected();

protected:
    Gallant::Signal1<Button*> mouse_enter_delegate_;
    Gallant::Signal1<Button*> mouse_exit_delegate_;
    Gallant::Signal2<Button*, const MouseButtonPressedEvent&> mouse_pressed_delegate_;
    Gallant::Signal2<Button*, const MouseMoveEvent&> mouse_dragged_delegate_;
    Gallant::Signal2<Button*, const MouseButtonReleasedEvent&> mouse_released_delegate_;
    Gallant::Signal1<Button*> on_select_delegate_;
    Gallant::Signal1<Button*> on_deselect_delegate_;

    Gallant::Delegate1<const Button*, bool> mouse_input_enabled_delegate_;
    bool mouse_entered_;
    int flags_;

    Node* node_;

    void mouseExitEvent(const MouseExitEvent& event);
    
};

NS_FT_END