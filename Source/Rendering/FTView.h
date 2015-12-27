#pragma once
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/FTNode.h>

// Subclass of FTNode which manages a camera
class FTView : public FTNode {
private:
    friend class FTScene;
public:
    explicit FTView() {
        view_ = this;
    }

    virtual ~FTView() {

    }

    void performDraw() {
        camera_->preDraw();
        FTNode::performDraw(camera_.get());
    }


    void setCamera(const std::shared_ptr<FTCamera>& camera) {
        camera_ = camera;
    }

    void setCamera(std::shared_ptr<FTCamera>&& camera) {
        camera_ = std::move(camera);
    }

    const std::shared_ptr<FTCamera>& getCamera() const {
        return camera_;
    }

protected:
    std::shared_ptr<FTCamera> camera_;
};
