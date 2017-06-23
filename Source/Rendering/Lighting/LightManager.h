#pragma once
#include <vector>
#include "Frontier.h"

NS_FT_BEGIN

struct LightDescriptor{
    // w == 0 indicates a directional light
    glm::vec4 position;
    glm::vec3 intensity;
    float attenuation;
    float ambientCoefficient;
    float coneAngle;
    glm::vec3 coneDirection;

    LightDescriptor() : attenuation(0), ambientCoefficient(0), coneAngle(0) {

    }
};

class LightManager {
public:
    static const int MaxLights = 5;
    LightManager() {
        lights_.reserve(5);
    }

    void addLight(const LightDescriptor& light) {
        FTAssert(lights_.size() < MaxLights, "Too many lights");
        lights_.push_back(light);
    }

    const std::vector<LightDescriptor>& getLights() const {
        return lights_;
    }

protected:
    std::vector<LightDescriptor> lights_;
};

NS_FT_END