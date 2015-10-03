#pragma once
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/FTDrawable.h>
#include <FTEngine.h>
#include <Event/FTEventManager.h>
#include <Event/Window/FTWindowEventDispatcher.h>
#include <stack>

class IFTView {
public:
    virtual ~IFTView() {
    }

    virtual void visit() = 0;

};

// Base class for all direct children of FTScene
// Manages a camera object and uses it to draw to a section of the screen
template <typename Camera>
class FTView : public IFTView {
    static_assert(std::is_base_of<FTCamera, Camera>::value, "FTCamera not base of Camera type");
public:
    FTView(const std::shared_ptr<Camera>& camera, const FTRect<float>& layer_rect) : camera_(camera), layer_rect_(layer_rect) {
        glm::vec2 screensize = FTEngine::getDirector()->getWindowSize();
        camera_->setScreenRect(FTRect<int>((int)(layer_rect.x_ * screensize.x), (int)(layer_rect.y_ * screensize.y), (int)(layer_rect.width_ * screensize.x), (int)(layer_rect.height_ * screensize.y)));

        auto screensize_changed_delegate = Gallant::Delegate1<const FTWindowResizeEvent&>(this, &FTView<Camera>::screensizeChanged);
        FTEngine::getEventManager()->getEventDispatcher<FTWindowEventDispatcher>()->registerDelegate(screensize_changed_delegate);
    }

    virtual ~FTView() {
        auto screensize_changed_delegate = Gallant::Delegate1<const FTWindowResizeEvent&>(this, &FTView<Camera>::screensizeChanged);
        FTEngine::getEventManager()->getEventDispatcher<FTWindowEventDispatcher>()->unregisterDelegate(screensize_changed_delegate);
    }

    virtual void visitChildren(const std::shared_ptr<FTCamera>& camera, std::stack<glm::mat4>& matrix_stack) = 0;

    virtual void visit() override {
        camera_->preDraw();
        std::stack<glm::mat4> matrix_stack;
        matrix_stack.push(glm::mat4());
        visitChildren(camera_, matrix_stack);
    }

protected:
    std::shared_ptr<Camera> camera_;

    // Screen rect in fractional values (i.e between 0 and 1)
    FTRect<float> layer_rect_;

    void screensizeChanged(const FTWindowResizeEvent& event) {
        camera_->setScreenRect(FTRect<int>((int)(layer_rect_.x_ * event.width_), (int)(layer_rect_.y_ * event.height_), (int)(layer_rect_.width_ * event.width_), (int)(layer_rect_.height_ * event.height_)));
    }
};
