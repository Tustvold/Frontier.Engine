#include "FTShaderNode.h"
#include "Rendering/Camera/FTCamera.h"

void FTShaderNode::pre_draw(const FTCamera *camera) {
    current_shader_program_->use();
    current_shader_program_->updateUniforms(camera, this);
}