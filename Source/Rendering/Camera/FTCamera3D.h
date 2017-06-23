#pragma once
#include <Util/FTRect.h>
#include <Rendering/Camera/FTCamera.h>
#include <Util/FTMath.h>

NS_FT_BEGIN

class FTCamera3D : public FTCamera {
public:
    explicit FTCamera3D();

    virtual ~FTCamera3D();
    
    void visit() override;

    void setPosition(const glm::vec3& pos) {
        view_matrix_dirty_ = true;
        position_ = pos;
    }

    void setFov(float fov) {
        projection_matrix_dirty_ = true;
        fov_ = fov;
    }

    void setRotation(const glm::quat& rotation) {
        rotation_ = rotation;
        rotation_dirty_ = true;
        view_matrix_dirty_ = true;
    }

    const glm::quat& getRotation() const {
        return rotation_;
    }

    void setShouldUpdateViewFrustrum(bool should_update_view_frustrum) {
        update_view_frustrum_ = should_update_view_frustrum;
    }

    bool testBoundingBox(const glm::vec3& aab_origin, const glm::vec3& aab_half_extents) const override;

    // Specify the up and look vectors for when there is no rotation applied
    void setAxes(const glm::vec3& up_axis, const glm::vec3& look_axis) {
        up_axis_ = up_axis;
        look_axis_ = look_axis;
        right_axis_ = glm::cross(look_axis, up_axis);
        rotation_dirty_ = true;
    }

    const glm::vec3& getUpVector() const {
        return up_vector_;
    }

    const glm::vec3& getForwardVector() const {
        return look_vector_;
    }

    FTRaycast generateRaycastForMousePos(double x, double y) override;

    glm::vec3 unProject(const glm::vec3& mouse_pos) override {
        if (view_projection_matrix_inv_dirty_) {
            view_projection_matrix_inv_ = glm::inverse(view_projection_matrix_);
        }
        auto clip_space = convertScreenSpaceToNDC(mouse_pos);

        glm::vec4 obj = view_projection_matrix_inv_ * glm::vec4(clip_space,1);
        obj /= obj.w;

        return glm::vec3(obj);
    }

protected:

    glm::vec4 frustrum_planes_[6];
    glm::vec3 frustrum_planes_sign_flipped_[6];

    // View Matrix parameters
    glm::quat rotation_;
    bool rotation_dirty_;
    bool update_view_frustrum_;
    
    // Specify the default orientation of the camera
    glm::vec3 up_axis_;
    glm::vec3 right_axis_;
    glm::vec3 look_axis_;

    // The actual direction vectors, post rotation
    glm::vec3 up_vector_;
    glm::vec3 right_vector_;
    glm::vec3 look_vector_;
    

    // Projection Matrix parameters
    float fov_;

private:

    void regenerateViewFrustrum();
};

NS_FT_END
