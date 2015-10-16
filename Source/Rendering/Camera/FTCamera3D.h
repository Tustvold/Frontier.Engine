#pragma once
#include <Util/FTRect.h>
#include <Rendering/Camera/FTCamera.h>
#include <Util/FTMath.h>

// Not threadsafe
class FTCamera3D : public FTCamera {
public:
    explicit FTCamera3D();

    virtual ~FTCamera3D();

    void preDraw() override;

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

    bool testBoundingBox(glm::vec3& center, glm::vec3& halfextents) const;

    bool testNodeVisible(const FTNode* node) const override;

    const glm::vec3& getUpVector() {
        return up_vector_;
    }

    const glm::vec3& getForwardVector() {
        return look_direction_;
    }

    FTRaycast generateRaycastForMousePos(double x, double y) override;

protected:

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

    void regenerateViewFrustrum();
};
