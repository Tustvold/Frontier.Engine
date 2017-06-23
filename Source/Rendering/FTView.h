#pragma once
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/FTNode.h>
#include <Rendering/Lighting/LightManager.h>

NS_FT_BEGIN

// Subclass of FTNode which manages a camera
class FTView : public FTNode {
private:
    friend class FTScene;
public:
    FTView() : light_manager_(new LightManager()){
        view_ = this;
    }

    virtual ~FTView() {

    }

    using FTNode::performDraw;
    void performDraw(uint32_t& draw_order) {
        camera_->visit();
        camera_->preDraw();
        FTNode::performDraw(camera_.get(), draw_order);
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

    const std::shared_ptr<LightManager>& getLightManager() const {
        return light_manager_;
    }

protected:
    std::shared_ptr<FTCamera> camera_;
    std::shared_ptr<LightManager> light_manager_;
};

NS_FT_END