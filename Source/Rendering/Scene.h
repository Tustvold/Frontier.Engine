#pragma once
#include <Frontier.h>
#include <Rendering/View.h>
#include <vector>

NS_FT_BEGIN

class Scene {
    friend class Director;
public:
    Scene() : is_active_(false) {

    }

    explicit Scene(const std::shared_ptr<View>& view) : is_active_(false) {
        addView(view);
    }

    explicit Scene(std::shared_ptr<View>&& view) : is_active_(false) {
        addView(std::move(view));
    }

    virtual ~Scene() {

    }

    virtual void visit() {
        for (auto it = views_.begin(); it != views_.end(); ++it) {
            (*it)->visit(glm::mat4(), false);
        }
    }

    virtual void draw() {
        uint32_t draw_order = 0;
        for (auto it = views_.begin(); it != views_.end(); ++it) {
            (*it)->performDraw(draw_order);
        }
    }

    void addView(const std::shared_ptr<View>& layer) {
        views_.push_back(layer);
        layer->onAddedToScene(this);
        if (is_active_)
            layer->onEnter();
    }

    void addView(std::shared_ptr<View>&& layer) {
        auto layer_ptr = layer.get();
        views_.push_back(std::move(layer));
        layer_ptr->onAddedToScene(this);
        if (is_active_)
            layer_ptr->onEnter();
    }

protected:

    virtual void onEnter() {
        FTAssert(!is_active_, "onEnter called on already entered scene");
        is_active_ = true;
        for (auto it = views_.begin(); it != views_.end(); ++it) {
            (*it)->onEnter();
        }
    }

    virtual void onExit() {
        FTAssert(is_active_, "onExit called on already exited scene");
        is_active_ = false;
        for (auto it = views_.begin(); it != views_.end(); ++it) {
            (*it)->onExit();
        }
    }

private:
    std::vector<std::shared_ptr<View>> views_;
    bool is_active_;
};

NS_FT_END