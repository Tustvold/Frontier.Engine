#pragma once
#include <Frontier.h>
#include <Rendering/FTView.h>
#include <vector>

// The root object of every scene, contains a list of the FTLayers to be drawn
class FTScene {
    friend class FTDirector;
public:
    explicit FTScene() : is_active_(false) {

    }

    virtual ~FTScene() {

    }

    virtual void draw() {
        for (auto it = views_.begin(); it != views_.end(); ++it) {
            (*it)->visit(glm::mat4(), false);
            (*it)->performDraw();
        }
    }

    void addView(const std::shared_ptr<FTView>& layer) {
        views_.push_back(layer);
        layer->onAddedToScene(this);
        if (is_active_)
            layer->onEnter();
    }

    void addView(std::shared_ptr<FTView>&& layer) {
        auto layer_ptr = layer.get();
        views_.push_back(std::move(layer));
        layer_ptr->onAddedToScene(this);
        if (is_active_)
            layer_ptr->onEnter();
    }

protected:

    virtual void onEnter() {
        is_active_ = true;
        for (auto it = views_.begin(); it != views_.end(); ++it) {
            (*it)->onEnter();
        }
    }

    virtual void onExit() {
        is_active_ = false;
        for (auto it = views_.begin(); it != views_.end(); ++it) {
            (*it)->onExit();
        }
    }

private:
    std::vector<std::shared_ptr<FTView>> views_;
    bool is_active_;
};
