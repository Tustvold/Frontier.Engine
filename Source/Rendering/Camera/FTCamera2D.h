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
        auto transformed = unProject(glm::vec3(x, y, 0));

        return FTRaycast(glm::vec3(transformed.x, transformed.y, 0.0f), glm::vec3(0, 0, -1.0f));
    }

    glm::vec3 unProject(const glm::vec3& mouse_pos) override {
        return glm::vec3(mouse_pos.x - draw_rect_abs_.x_, mouse_pos.y - draw_rect_abs_.y_, 0);
    }

    void visit() override;

    bool testNodeVisible(const FTNode* node) const override;
};
