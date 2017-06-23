#pragma once

#include <Rendering/Camera/Camera.h>
#include <glm/gtc/matrix_transform.hpp>

NS_FT_BEGIN

class Camera2D : public Camera {
public:


    Camera2D() {
        setClippingPlanes(0, 1);
    }

    virtual ~Camera2D() {

    }

    Raycast generateRaycastForMousePos(double x, double y) override {
        auto transformed = unProject(glm::vec3(x, y, 0));

        return Raycast(glm::vec3(transformed.x, transformed.y, 0.0f), glm::vec3(0, 0, -1.0f));
    }

    glm::vec3 unProject(const glm::vec3& mouse_pos) override {
        return glm::vec3(mouse_pos.x - draw_rect_abs_.x_, mouse_pos.y - draw_rect_abs_.y_, 0);
    }

    void visit() override;

    bool testBoundingBox(const glm::vec3& aab_origin, const glm::vec3& aab_half_extents) const override;
};

NS_FT_END