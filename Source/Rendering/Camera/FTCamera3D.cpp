#include "FTCamera3D.h"
#include <glm/gtc/matrix_access.hpp>
#include <Rendering/FTDirector.h>
#include <Rendering/Scene/FTNode.h>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_vec4.hpp>


FTCamera3D::FTCamera3D() : position_(0, 0, 0), rotation_euler_radians(0, 0), rotation_dirty_(true), update_view_frustrum_(true), fov_(45) {
    
};

FTCamera3D::~FTCamera3D() {
    
}


bool FTCamera3D::testNodeVisible(const FTNodeBase* node) const {
    glm::vec3 half_extents = node->getAABHalfExtents();
    glm::vec3 center = node->getAABCenter();
    
    return testBoundingBox(center, half_extents);
}

bool FTCamera3D::testBoundingBox(glm::vec3& center, glm::vec3& halfextents) const {
    for (int i = 0; i < 6; i++) {
        glm::vec3 res = center + vec3xor(halfextents, frustrum_planes_sign_flipped_[i]);
        if (glm::dot(res, *(glm::vec3*)&(frustrum_planes_[i].getConstData())) <= -frustrum_planes_[i].getConstData().w)
            return false;
    }
    return true;
}

glm::vec4 normalizeVec4(const glm::vec4& vec) {
    glm::vec3 xyz(vec);
    float d = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    return vec / d;
}

float InvSqrt(float x) {
    float xhalf;
    int i;

    xhalf = 0.5f * x;
    i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x * (1.5f - xhalf * x * x);
    return x;
}

static inline float floatAnd(float f) {

    int i = ((*(int*)&f) & 0x80000000);
    return (*(float*)&i);
}

void FTCamera3D::regenerateViewFrustrum() {
    glm::mat4 matrix = projection_matrix_.getData() * view_matrix_.getData();
    glm::vec4 row1 = glm::row(matrix, 0);
    glm::vec4 row2 = glm::row(matrix, 1);
    glm::vec4 row3 = glm::row(matrix, 2);
    glm::vec4 row4 = glm::row(matrix, 3);

    // Near Plane
    glm::vec4& data0 = frustrum_planes_[0].getData();
    data0 = normalizeVec4(row4 + row3);
    frustrum_planes_sign_flipped_[0] = glm::vec3(floatAnd(data0.x), floatAnd(data0.y), floatAnd(data0.z));
    // Far Plane
    glm::vec4& data1 = frustrum_planes_[1].getData();
    data1 = normalizeVec4(row4 - row3);
    frustrum_planes_sign_flipped_[1] = glm::vec3(floatAnd(data1.x), floatAnd(data1.y), floatAnd(data1.z));

    // Left Plane
    glm::vec4& data2 = frustrum_planes_[2].getData();
    data2 = normalizeVec4(row4 + row1);
    frustrum_planes_sign_flipped_[2] = glm::vec3(floatAnd(data2.x), floatAnd(data2.y), floatAnd(data2.z));

    // Right Plane
    glm::vec4& data3 = frustrum_planes_[3].getData();
    data3 = normalizeVec4(row4 - row1);
    frustrum_planes_sign_flipped_[3] = glm::vec3(floatAnd(data3.x), floatAnd(data3.y), floatAnd(data3.z));

    // Top Plane
    glm::vec4& data4 = frustrum_planes_[4].getData();
    data4 = normalizeVec4(row4 + row2);
    frustrum_planes_sign_flipped_[4] = glm::vec3(floatAnd(data4.x), floatAnd(data4.y), floatAnd(data4.z));

    // Bottom Plane
    glm::vec4& data5 = frustrum_planes_[5].getData();
    data5 = normalizeVec4(row4 - row2);
    frustrum_planes_sign_flipped_[5] = glm::vec3(floatAnd(data5.x), floatAnd(data5.y), floatAnd(data5.z));
}
