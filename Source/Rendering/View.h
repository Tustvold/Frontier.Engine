#pragma once
#include <Rendering/Camera/Camera.h>
#include <Rendering/Node.h>
#include <Rendering/Lighting/LightManager.h>

NS_FT_BEGIN

// Subclass of Node which manages a camera
class View : public Node {
private:
    friend class Scene;
public:
    View() : light_manager_(new LightManager()){
        view_ = this;
    }

    virtual ~View() {

    }

    using Node::performDraw;
    void performDraw(uint32_t& draw_order) {
        camera_->visit();
        camera_->preDraw();
        Node::performDraw(camera_.get(), draw_order);
    }


    void setCamera(const std::shared_ptr<Camera>& camera) {
        camera_ = camera;
    }

    void setCamera(std::shared_ptr<Camera>&& camera) {
        camera_ = std::move(camera);
    }

    const std::shared_ptr<Camera>& getCamera() const {
        return camera_;
    }

    const std::shared_ptr<LightManager>& getLightManager() const {
        return light_manager_;
    }

protected:
    std::shared_ptr<Camera> camera_;
    std::shared_ptr<LightManager> light_manager_;
};

NS_FT_END