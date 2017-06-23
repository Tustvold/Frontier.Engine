#pragma once
#include "Frontier.h"
#include "Rendering/Texture/Texture.h"

NS_FT_BEGIN

// A store for variables used by shaders
// Note that not all shaders will use all of these variables
// However, as material's can be shared, the increased memory footprint
// is outweighed by the performance boost from simply storing all of them
struct Material {
    std::shared_ptr<Texture> texture;
    float shininess;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    float border_thickness;

    Material() : shininess(1), diffuse_color(0,0,0), specular_color(0,0,0), border_thickness(0) {

    }
};

NS_FT_END