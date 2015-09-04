#pragma once
#include <Rendering/Scene/FTView.h>
#include <vector>
#include <memory>

// The root object of every scene, contains a list of the FTLayers to be drawn
class FTScene {
public:
    explicit FTScene() {

    }

    virtual ~FTScene() {

    }

    virtual void draw() {
        for (auto it = views_.begin(); it != views_.end(); ++it) {
            (*it)->draw();
        }
    }

    void addView(std::shared_ptr<IFTView>& layer) {
        views_.push_back(layer);
    }

private:
    std::vector<std::shared_ptr<IFTView>> views_;
};
