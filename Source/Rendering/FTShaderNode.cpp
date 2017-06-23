#include "FTShaderNode.h"
#include "Rendering/Camera/FTCamera.h"

NS_FT_BEGIN

void FTShaderNode::pre_draw(const FTCamera *camera) {
    current_shader_program_->use();
    current_shader_program_->updateUniforms(camera, this);
}

NS_FT_END