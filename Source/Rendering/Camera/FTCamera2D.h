#pragma once

#include <Rendering/Camera/FTCamera.h>
#include <Util/FTAlignedData.h>
#include <glm/gtc/matrix_transform.hpp>

class FTCamera2D : public FTCamera {
public:

    FTCamera2D() {
        setClippingPlanes(0, 1);
    }

    virtual ~FTCamera2D() {

    }

    const glm::mat4& getViewMatrix() const override {
        return view_matrix.getConstData();
    }

    const glm::mat4& getProjectionMatrix() const override {
        return projection_matrix_.getConstData();
    }

    const glm::mat4& getViewProjectionMatrix() const override {
        return projection_matrix_.getConstData();
    }

    void preDraw() override {
        FTCamera::preDraw();
        if (projection_matrix_dirty_) {
            projection_matrix_ = glm::ortho<float>(0, (float)screen_rect_.width_, 0, (float)screen_rect_.height_, near_clipping_plane_, far_clipping_plane_);
            projection_matrix_dirty_ = false;
        }
    }

    bool testBoundingBox(glm::vec3& center, glm::vec3& halfextents) const override {
        return true;
    }

    bool testNodeVisible(const FTNodeBase* node) const override {
        auto& position = node->getPosition();
        auto& size = node->getSize();

        return position.x <= screen_rect_.x_ + screen_rect_.width_ && position.x + size.x >= screen_rect_.x_ && position.y <= screen_rect_.y_ + screen_rect_.height_ && position.y + size.y >= screen_rect_.y_;
    }

private:
    FTAlignedData<glm::mat4> projection_matrix_;
    FTAlignedData<glm::mat4> view_matrix;
};
