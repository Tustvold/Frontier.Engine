#include "FTPlane.h"

NS_FT_BEGIN

FTPlane::FTPlane(const glm::vec2& dimensions, const glm::vec3& color, FTVertexShaderProgramColor* shader):
    FTPolygon(color, shader) {
    loadFilledPolygon(std::vector<glm::vec2>({
        glm::vec2(0, 0),
        glm::vec2(dimensions.x, 0),
        glm::vec2(dimensions.x, dimensions.y),
        glm::vec2(0, dimensions.y)
    }), dimensions);
}

NS_FT_END