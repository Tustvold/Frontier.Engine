#include "BoundingShape.h"
#include <Util/Math.h>
#include <Rendering/Node.h>

NS_FT_BEGIN

void BoundingShape::computeWorldAABFromLocalAAB(const glm::vec3& origin, const glm::vec3& size, glm::vec3& world_aab_origin, glm::vec3& world_aab_half_extents) const {
    auto& model_matrix = node_->getModelMatrix();
    auto min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    auto max = glm::vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    glm::vec4 positions[8] = {
        glm::vec4(origin.x, origin.y, origin.z, 1),
        glm::vec4(origin.x + size.x, origin.y, origin.z, 1),
        glm::vec4(origin.x, origin.y + size.y, origin.z, 1),
        glm::vec4(origin.x, origin.y, origin.z + size.z, 1),
        glm::vec4(origin.x + size.x, origin.y + size.y, origin.z, 1),
        glm::vec4(origin.x + size.x, origin.y, origin.z + size.z, 1),
        glm::vec4(origin.x, origin.y + size.y, origin.z + size.z, 1),
        glm::vec4(origin.x + size.x, origin.y + size.y, origin.z + size.z, 1),
    };

    for (int i = 0; i < 8; i++) {
        auto transformed = model_matrix * positions[i];
        max.x = FTMAX(transformed.x, max.x);
        max.y = FTMAX(transformed.y, max.y);
        max.z = FTMAX(transformed.z, max.z);

        min.x = FTMIN(transformed.x, min.x);
        min.y = FTMIN(transformed.y, min.y);
        min.z = FTMIN(transformed.z, min.z);
    }

    world_aab_half_extents = (max - min) / 2.0f;
    world_aab_origin = (max + min) / 2.0f;
}

BoundingShape::BoundingShape() : anchor_point_transform_(new TransformPosition()), node_(nullptr), dirty_(true) {

}

bool BoundingShape::containsMousePosition(const glm::vec2& mouse_pos) {
    return containsLocalPosition(node_->convertMouseToLocalCoordinates(mouse_pos));
}

void BoundingShape::updateMatrices() {
    anchor_point_transform_->setPosition(-computeLocalOffset(node_->getAnchorPoint()));
}

NS_FT_END