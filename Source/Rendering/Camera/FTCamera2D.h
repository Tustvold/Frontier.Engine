#pragma once

#include <Rendering/Camera/FTCamera.h>
#include <glm/gtc/matrix_transform.hpp>

class FTCamera2D : public FTCamera {
public:


    FTCamera2D() {
        setClippingPlanes(0, 1);
    }

    virtual ~FTCamera2D() {

    }

    FTRaycast generateRaycastForMousePos(double x, double y) override {
        return FTRaycast(glm::vec3((float)x, (float)y, 0.0f), glm::vec3(0, 0, -1.0f));
    }

    void preDraw() override;

    bool testNodeVisible(const FTNode* node) const override;
};
