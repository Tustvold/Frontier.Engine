#pragma once
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/FTNode.h>

// Subclass of FTNode which manages a camera
class FTView : public FTNode {
    friend class FTScene;
public:
    explicit FTView() {
        view_ = this;
    }

    virtual ~FTView() {

    }

    virtual void visit() {
        camera_->preDraw();
        std::stack<glm::mat4> matrix_stack;
        matrix_stack.push(glm::mat4());
        FTNode::visit(camera_.get(), matrix_stack, false);
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
