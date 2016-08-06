#include "FTBoundingShape.h"
#include <Util/FTMath.h>
#include <Rendering/FTNode.h>


void FTBoundingShape::computeWorldAABFromLocalAAB(const glm::vec3& origin, const glm::vec3& size, glm::vec3& world_aab_origin, glm::vec3& world_aab_half_extents) const {
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

FTBoundingShape::FTBoundingShape() : anchor_point_transform_(new FTTransformPosition()), node_(nullptr), dirty_(true) {

}

bool FTBoundingShape::containsMousePosition(const glm::vec2& mouse_pos) {
    return containsLocalPosition(node_->convertMouseToLocalCoordinates(mouse_pos));
}

void FTBoundingShape::updateMatrices() {
    anchor_point_transform_->setPosition(-computeLocalOffset(node_->getAnchorPoint()));
}
