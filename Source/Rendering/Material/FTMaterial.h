#pragma once
#include "Frontier.h"
#include "Rendering/Texture/FTTexture.h"

// A store for variables used by shaders
// Note that not all shaders will use all of these variables
// However, as material's can be shared, the increased memory footprint
// is outweighed by the performance boost from simply storing all of them
struct FTMaterial {
    std::shared_ptr<FTTexture> texture;
    float shininess;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    float border_thickness;

    FTMaterial() : shininess(1), diffuse_color(0,0,0), specular_color(0,0,0), border_thickness(0) {

    }
};
