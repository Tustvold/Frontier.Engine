#include "Cube.h"
#include <Rendering/Shader/ShaderCache.h>
#include <Rendering/BoundingShape/BoundingCuboid.h>

NS_FT_BEGIN

Cube::Cube(const glm::vec3& color, VertexColorShaderProgram* shader) : Cuboid(glm::vec3(0,0,0), glm::vec3(1,1,1), color, shader) {
}

Cube::Cube(const glm::vec3 face_colors[6], VertexColorShaderProgram* shader)
    : Cuboid(glm::vec3(0,0,0), glm::vec3(1,1,1), face_colors, shader) {
}

Cube::~Cube() {

}

NS_FT_END