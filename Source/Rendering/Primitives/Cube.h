#pragma once
#include "Cuboid.h"

NS_FT_BEGIN

class Cube : public Cuboid {
public:
    explicit Cube(const glm::vec3& color, VertexColorShaderProgram* shader = ShaderNode::getShaderUtil<VertexColorShaderProgram>());

    explicit Cube(const glm::vec3 face_colors[6], VertexColorShaderProgram* shader = ShaderNode::getShaderUtil<VertexColorShaderProgram>());
    ~Cube();
};

NS_FT_END