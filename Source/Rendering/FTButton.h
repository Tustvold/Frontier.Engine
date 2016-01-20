#pragma once
#include <Event/Input/FTMouseDelegate.h>

class FTNode;
// Wraps around an FTNode and performs intersection tests based on its bounding shape
// Exposes four delgates:
// mouse_enter - invoked when the mouse hovers over the button
// mouse_exit - invoked when the mouse leaves the area above the button
// mouse_pressed - invoked when the left mouse button is pressed whilst hovering above the button (invoked after mouse_enter)
// mouse_released - invoked when the left mouse button is released whilst the cursor is above the button having also been pressed whilst the cursor was above the button
class FTButton : public FTMouseDelegate {

public:
    enum Flags {
        ClickDelegatesEnabled = 1,
        SelectDelegatesEnabled = 1 << 1,
        EnterExitDelegatesEnabled = 1 << 2,
    };


    explicit FTButton(FTNode* renderer);
    
    virtual ~FTButton();

    bool onMouseDown(const FTMouseButtonPressedEvent& event) override;
    void onMouseDrag(const FTMouseMoveEvent&, int mouse_button) override;
    void onMouseRelease(const FTMouseButtonReleasedEvent& event) override;
    
    
    void onMouseMove(const FTMouseMoveEvent& event);

    template <class X, class Y>
    void bindMouseEnterDelegate(Y* pthis, void(X::* function_to_bind)(FTButton*)) {
        enableEnterExitDelegates();
        mouse_enter_delegate_.Bind(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMouseExitDelegate(Y* pthis, void(X::* function_to_bind)(FTButton*)) {
        enableEnterExitDelegates();
        mouse_exit_delegate_.Bind(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMousePressedDelegate(Y* pthis, bool(X::* function_to_bind)(FTButton*, const FTMouseButtonPressedEvent&)) {
        enableClickDelegates();
        mouse_pressed_delegate_.Bind(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMouseDragDelegate(Y* pthis, void(X::* function_to_bind)(FTButton*, const FTMouseMoveEvent&)) {
        enableClickDelegates();
        mouse_dragged_delegate_.Bind(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMouseReleasedDelegate(Y* pthis, void(X::* function_to_bind)(FTButton*, const FTMouseButtonReleasedEvent&)) {
        enableClickDelegates();
        mouse_released_delegate_.Bind(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindOnSelectDelegate(Y* pthis, void(X::* function_to_bind)(FTButton*)) {
        enableSelectDelegates();
        on_select_delegate_.Bind(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindOnDeselectDelegate(Y* pthis, void(X::* function_to_bind)(FTButton*)) {
        enableSelectDelegates();
        on_deselect_delegate_.Bind(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindEnabledDelegate(Y* pthis, bool(X::* function_to_bind)(const FTButton*)) {
        mouse_input_enabled_delegate_.Bind(pthis, function_to_bind);
    }

    bool getMouseDelegateEnabled() const override;

    FTNode* getNode() const {
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

    void enableClickDelegates();

    void enableSelectDelegates();

    void enableEnterExitDelegates();

    void setSelected();

    void setDeselected();

protected:
    Gallant::Delegate1<FTButton*> mouse_enter_delegate_;
    Gallant::Delegate1<FTButton*> mouse_exit_delegate_;
    Gallant::Delegate2<FTButton*, const FTMouseButtonPressedEvent&, bool> mouse_pressed_delegate_;
    Gallant::Delegate2<FTButton*, const FTMouseMoveEvent&> mouse_dragged_delegate_;
    Gallant::Delegate2<FTButton*, const FTMouseButtonReleasedEvent&> mouse_released_delegate_;
    Gallant::Delegate1<const FTButton*, bool> mouse_input_enabled_delegate_;
    Gallant::Delegate1<FTButton*> on_select_delegate_;
    Gallant::Delegate1<FTButton*> on_deselect_delegate_;
    bool mouse_entered_;
    int flags_;

    FTNode* node_;

    void mouseExitEvent(const FTMouseExitEvent& event);
    
};