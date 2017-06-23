#include "Plane.h"

NS_FT_BEGIN

Plane::Plane(const glm::vec2& dimensions, const glm::vec3& color, VertexShaderProgramColor* shader):
    Polygon(color, shader) {
    loadFilledPolygon(std::vector<glm::vec2>({
        glm::vec2(0, 0),
        glm::vec2(dimensions.x, 0),
        glm::vec2(dimensions.x, dimensions.y),
        glm::vec2(0, dimensions.y)
    }), dimensions);
}

NS_FT_END