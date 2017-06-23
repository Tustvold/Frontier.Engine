#include "FTCube.h"
#include <Rendering/Shader/FTShaderCache.h>
#include <Rendering/BoundingShape/FTBoundingCuboid.h>

NS_FT_BEGIN

FTCube::FTCube(const glm::vec3& color, FTVertexColorShaderProgram* shader) : FTCuboid(glm::vec3(0,0,0), glm::vec3(1,1,1), color, shader) {
}

FTCube::FTCube(const glm::vec3 face_colors[6], FTVertexColorShaderProgram* shader)
    : FTCuboid(glm::vec3(0,0,0), glm::vec3(1,1,1), face_colors, shader) {
}

FTCube::~FTCube() {

}

NS_FT_END