#pragma once

#include <Rendering/Lighting/LightManager.h>
#include "VertexColorShaderProgram.h"

NS_FT_BEGIN

class VertexShaderProgramLighting : public VertexColorShaderProgram {
public:

    VertexShaderProgramLighting();

    virtual ~VertexShaderProgramLighting();

    bool load() override;

    bool compile() override {
        return createShaderProgram(vertex_shader_source_, fragment_shader_source_);
    }

    void updateUniforms(const Camera *camera, ShaderNode *node) override;

private:
    static const char* fragment_shader_source_;
    static const char* vertex_shader_source_;

    GLint num_lights_uniform_;
    GLint material_shininess_uniform_;
    GLint material_specular_color_uniform_;
    GLint model_matrix_uniform_;
    GLint normal_matrix_uniform_;
    GLint camera_position_uniform_;

    GLint position_uniforms_[LightManager::MaxLights];
    GLint intensity_uniforms_[LightManager::MaxLights];
    GLint attenuation_uniforms_[LightManager::MaxLights];
    GLint ambient_coefficient_uniforms_[LightManager::MaxLights];
    GLint cone_angle_uniforms_[LightManager::MaxLights];
    GLint cone_direction_uniforms_[LightManager::MaxLights];
};

NS_FT_END
