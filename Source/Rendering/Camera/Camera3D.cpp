#include "Camera3D.h"
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Rendering/Node.h>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec4.hpp>

NS_FT_BEGIN

Camera3D::Camera3D() : rotation_dirty_(true), update_view_frustrum_(true), up_axis_(0,1,0), right_axis_(1,0,0), look_axis_(0,0,-1), fov_((float)M_PI_2) {
    setCullFaceEnabled(true);
    setDepthTestEnabled(true);
};

Camera3D::~Camera3D() {

}

void Camera3D::visit() {
    if (projection_matrix_dirty_) {
        projection_matrix_ = glm::perspective(fov_, (float)draw_rect_abs_.width_ / (float)draw_rect_abs_.height_, near_clipping_plane_, far_clipping_plane_);
    }
    if (view_matrix_dirty_) {
        if (rotation_dirty_) {
            up_vector_ = rotation_ * up_axis_;
            look_vector_ = rotation_ * look_axis_;
            right_vector_ = glm::cross(look_vector_, up_vector_);

            rotation_dirty_ = false;
        }
        view_matrix_ = glm::lookAt(position_, look_vector_ + position_, up_vector_);
    }
    if (view_matrix_dirty_ || projection_matrix_dirty_) {
        view_projection_matrix_ = projection_matrix_ * view_matrix_;
        if (update_view_frustrum_)
            regenerateViewFrustrum();
        view_matrix_dirty_ = false;
        projection_matrix_dirty_ = false;
        view_projection_matrix_inv_dirty_ = true;
    }
}

static inline glm::vec3 vec3xor(const glm::vec3 &av, const glm::vec3 &bv) {
    union converter_f {
        float f;
        int32_t i;
    };

    struct converter {
        converter_f x;
        converter_f y;
        converter_f z;
    };

    converter a, b, c;
    a.x.f = av.x;
    a.y.f = av.y;
    a.z.f = av.z;


    b.x.f = bv.x;
    b.y.f = bv.y;
    b.z.f = bv.z;

    c.x.i = a.x.i ^ b.x.i;
    c.y.i = a.y.i ^ b.y.i;
    c.z.i = a.z.i ^ b.z.i;
    return glm::vec3(c.x.f, c.y.f, c.z.f);
}

static inline float floatAnd(float f) {
    union converter_f {
        float f;
        int32_t i;
    };
    converter_f c;
    c.f = f;
    c.i = c.i & 0x80000000;

    return c.f;
}

bool Camera3D::testBoundingBox(const glm::vec3& aab_center, const glm::vec3& aab_half_extents) const {
    for (int i = 0; i < 6; i++) {
        glm::vec3 res = aab_center + vec3xor(aab_half_extents, frustrum_planes_sign_flipped_[i]);
        if (glm::dot(res, glm::vec3(frustrum_planes_[i])) <= -frustrum_planes_[i].w)
            return false;
    }
    return true;
}

Raycast Camera3D::generateRaycastForMousePos(double x, double y) {
    glm::vec3 near_vector = unProject(glm::vec3(x, y, 0));
    glm::vec3 far_vector = unProject(glm::vec3(x, y, 1));

    glm::vec3 direction = glm::vec3(far_vector.x - near_vector.x, far_vector.y - near_vector.y, far_vector.z - near_vector.z);
    direction = glm::normalize(direction);
    return Raycast(position_, direction);
}

glm::vec4 normalizeVec4(const glm::vec4& vec) {
    float d = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    return vec / d;
}

void Camera3D::regenerateViewFrustrum() {
    glm::mat4 matrix = projection_matrix_ * view_matrix_;
    glm::vec4 row1 = glm::row(matrix, 0);
    glm::vec4 row2 = glm::row(matrix, 1);
    glm::vec4 row3 = glm::row(matrix, 2);
    glm::vec4 row4 = glm::row(matrix, 3);

    // Near Plane
    glm::vec4& data0 = frustrum_planes_[0];
    data0 = normalizeVec4(row4 + row3);
    frustrum_planes_sign_flipped_[0] = glm::vec3(floatAnd(data0.x), floatAnd(data0.y), floatAnd(data0.z));
    // Far Plane
    glm::vec4& data1 = frustrum_planes_[1];
    data1 = normalizeVec4(row4 - row3);
    frustrum_planes_sign_flipped_[1] = glm::vec3(floatAnd(data1.x), floatAnd(data1.y), floatAnd(data1.z));

    // Left Plane
    glm::vec4& data2 = frustrum_planes_[2];
    data2 = normalizeVec4(row4 + row1);
    frustrum_planes_sign_flipped_[2] = glm::vec3(floatAnd(data2.x), floatAnd(data2.y), floatAnd(data2.z));

    // Right Plane
    glm::vec4& data3 = frustrum_planes_[3];
    data3 = normalizeVec4(row4 - row1);
    frustrum_planes_sign_flipped_[3] = glm::vec3(floatAnd(data3.x), floatAnd(data3.y), floatAnd(data3.z));

    // Top Plane
    glm::vec4& data4 = frustrum_planes_[4];
    data4 = normalizeVec4(row4 + row2);
    frustrum_planes_sign_flipped_[4] = glm::vec3(floatAnd(data4.x), floatAnd(data4.y), floatAnd(data4.z));

    // Bottom Plane
    glm::vec4& data5 = frustrum_planes_[5];
    data5 = normalizeVec4(row4 - row2);
    frustrum_planes_sign_flipped_[5] = glm::vec3(floatAnd(data5.x), floatAnd(data5.y), floatAnd(data5.z));
}

NS_FT_END