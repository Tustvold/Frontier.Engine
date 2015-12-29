#pragma once
#include "FTNode.h"

// Wraps around an FTNode and performs a simple 2D intersection test based on its size.
// Exposes four delgates:
// mouse_enter - invoked when the mouse hovers over the button
// mouse_exit - invoked when the mouse leaves the area above the button
// mouse_pressed - invoked when the left mouse button is pressed whilst hovering above the button (invoked after mouse_enter)
// mouse_released - invoked when the left mouse button is released whilst the cursor is above the button having also been pressed whilst the cursor was above the button
class FTButton2D : public FTNode {

public:
    
    explicit FTButton2D(const std::shared_ptr<FTNode>& renderer);
    explicit FTButton2D(std::shared_ptr<FTNode>&& renderer);
    
    virtual ~FTButton2D();

    virtual bool rendererContainsMousePoint(double x, double y);

    bool onMouseDown(const FTMouseButtonPressedEvent& event) override;
    void onMouseDrag(const FTMouseMoveEvent&, int mouse_button) override;
    void onMouseRelease(const FTMouseButtonReleasedEvent& event) override;
    bool onMouseMove(const FTMouseMoveEvent& event) override;

    template <class X, class Y>
    void bindMouseEnterDelegate(Y* pthis, void(X::* function_to_bind)()) {
        mouse_enter_delegate_.Bind(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMouseExitDelegate(Y* pthis, void(X::* function_to_bind)()) {
        mouse_exit_delegate_.Bind(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMousePressedDelegate(Y* pthis, void(X::* function_to_bind)()) {
        mouse_pressed_delegate_.Bind(pthis, function_to_bind);
    }

    template <class X, class Y>
    void bindMouseReleasedDelegate(Y* pthis, void(X::* function_to_bind)()) {
        mouse_released_delegate_.Bind(pthis, function_to_bind);
    }

    const glm::vec3& getScale() const override {
        return renderer_->getScale();
    }

    const glm::vec3& getSize() const override {
        return renderer_->getSize();
    }

protected:
    Gallant::Delegate0<> mouse_enter_delegate_;
    Gallant::Delegate0<> mouse_exit_delegate_;
    Gallant::Delegate0<> mouse_pressed_delegate_;
    Gallant::Delegate0<> mouse_released_delegate_;

    bool mouse_entered_;

    std::shared_ptr<FTNode> renderer_;

    void mouseExitEvent(const FTMouseExitEvent& event);
};