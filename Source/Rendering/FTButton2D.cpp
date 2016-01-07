#include "FTButton2D.h"
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include "FTView.h"

FTButton2D::FTButton2D(const std::shared_ptr<FTNode>& renderer) :
        tag_(0), 
        mouse_entered_(false),
        renderer_(renderer) {
    addChild(renderer);
    setMouseInputEnabled(true);
    setSize(renderer_->getSize());
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTButton2D::mouseExitEvent);
}

FTButton2D::FTButton2D(std::shared_ptr<FTNode>&& renderer) :
        tag_(0),
        mouse_entered_(false),
        renderer_(std::move(renderer)) {
    addChild(renderer_);
    setMouseInputEnabled(true);
    setSize(renderer_->getSize());
    FTEngine::getEventManager()->registerDelegate<FTMouseEventDispatcher>(this, &FTButton2D::mouseExitEvent);
}

FTButton2D::~FTButton2D() {
    FTEngine::getEventManager()->unregisterDelegate<FTMouseEventDispatcher>(this, &FTButton2D::mouseExitEvent);
}

bool FTButton2D::rendererContainsMousePoint(double x, double y) {
    auto local_pos = renderer_->convertMouseToLocalCoordinates(glm::vec2(x, y));

    auto& size = renderer_->getSize();
    return local_pos.x >= 0 && local_pos.y >= 0 && local_pos.x <= size.x && local_pos.y <= size.y;
}

bool FTButton2D::onMouseDown(const FTMouseButtonPressedEvent& event) {
    if (event.mouse_button_ != GLFW_MOUSE_BUTTON_LEFT || !rendererContainsMousePoint(event.cursor_x_, event.cursor_y_))
        return false;

    if (!mouse_pressed_delegate_.empty())
        mouse_pressed_delegate_(this);
    return true;
}

void FTButton2D::onMouseDrag(const FTMouseMoveEvent&, int mouse_button) {

}

void FTButton2D::onMouseRelease(const FTMouseButtonReleasedEvent& event) {
    if (event.mouse_button_ != GLFW_MOUSE_BUTTON_LEFT || !rendererContainsMousePoint(event.cursor_x_, event.cursor_y_))
        return;
    if (!mouse_released_delegate_.empty())
        mouse_released_delegate_(this);
}

bool FTButton2D::onMouseMove(const FTMouseMoveEvent& event) {
    auto contains = rendererContainsMousePoint(event.x_, event.y_);
    if (contains == mouse_entered_)
        return contains;
    if (contains) {
        if (!mouse_enter_delegate_.empty())
            mouse_enter_delegate_(this);
    } else {
        if (!mouse_exit_delegate_.empty())
            mouse_exit_delegate_(this);
    }
    mouse_entered_ = contains;
    return contains;
}

void FTButton2D::mouseExitEvent(const FTMouseExitEvent& event) {
    if (mouse_entered_) {
        if (!mouse_exit_delegate_.empty())
            mouse_exit_delegate_(this);
        mouse_entered_ = false;
    }
}