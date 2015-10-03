#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Frontier.h>
#include <Util/FTAlignedData.h>
#include <Util/FTRect.h>
#include <Rendering/Camera/FTCamera.h>
#include <Util/FTMath.h>

// Not threadsafe
class FTCamera3D : public FTCamera {
public:
    explicit FTCamera3D();

    virtual ~FTCamera3D();

    const glm::mat4& getViewMatrix() const override {
        return view_matrix_.getConstData();
    }

    const glm::mat4& getProjectionMatrix() const override {
        return projection_matrix_.getConstData();
    }

    const glm::mat4& getViewProjectionMatrix() const override {
        return view_projection_matrix_.getConstData();
    }

    void preDraw() override {
        FTCamera::preDraw();
        if (projection_matrix_dirty_) {
            projection_matrix_ = glm::perspective(fov_, (float)screen_rect_.width_ / (float)screen_rect_.height_, near_clipping_plane_, far_clipping_plane_);
        }
        if (view_matrix_dirty_) {
            if (rotation_dirty_) {
                look_direction_ = glm::vec3(cos(rotation_euler_radians.y) * sin(rotation_euler_radians.x), sin(rotation_euler_radians.y), cos(rotation_euler_radians.y) * -cos(rotation_euler_radians.x));

                right_vector_ = glm::vec3(cos(rotation_euler_radians.x), 0, sin(rotation_euler_radians.x));
                up_vector_ = glm::cross(right_vector_, look_direction_);

                rotation_dirty_ = false;
            }
            view_matrix_ = glm::lookAt(position_, look_direction_ + position_, up_vector_);
        }
        if (view_matrix_dirty_ || projection_matrix_dirty_) {
            view_projection_matrix_ = projection_matrix_.getData() * view_matrix_.getData();
            if (update_view_frustrum_)
                regenerateViewFrustrum();
            view_matrix_dirty_ = false;
            projection_matrix_dirty_ = false;
        }
    }

    void setUpVector(const glm::vec3& up_vector) {
        view_matrix_dirty_ = true;
        up_vector_ = up_vector;
    }

    void setPosition(const glm::vec3& pos) {
        view_matrix_dirty_ = true;
        position_ = pos;
    }

    void setFov(float fov) {
        projection_matrix_dirty_ = true;
        fov_ = fov;
    }

    void setRotationRadians(const glm::vec2& rotation) {
        rotation_euler_radians = rotation;
        rotation_dirty_ = true;
        view_matrix_dirty_ = true;
    }

    void setRotationDegrees(const glm::vec2& rotation) {
        setRotationRadians(rotation * DEG2RAD);
    }

    const glm::vec3& getPosition() {
        return position_;
    }

    void setShouldUpdateViewFrustrum(bool should_update_view_frustrum) {
        update_view_frustrum_ = should_update_view_frustrum;
    }

    bool testBoundingBox(glm::vec3& center, glm::vec3& halfextents) const override;

    bool testNodeVisible(const FTNodeBase* node) const override;

protected:

    FTAlignedData<glm::mat4> projection_matrix_;
    FTAlignedData<glm::mat4> view_matrix_;
    FTAlignedData<glm::mat4> view_projection_matrix_;

    FTAlignedData<glm::vec4> frustrum_planes_[6];
    glm::vec3 frustrum_planes_sign_flipped_[6];

    // View Matrix parameters
    glm::vec3 position_;
    glm::vec3 look_direction_;
    glm::vec3 up_vector_;
    glm::vec3 right_vector_;
    glm::vec2 rotation_euler_radians;
    bool rotation_dirty_;
    bool update_view_frustrum_;

    // Projection Matrix parameters
    float fov_;

private:

    /*void screensizeChange(float width, float height) {
		screen_size_ = glm::vec2(width, height);
		projection_matrix_dirty_ = true;
	}*/

    void regenerateViewFrustrum();
};
