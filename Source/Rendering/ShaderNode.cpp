#include "ShaderNode.h"
#include "Rendering/Camera/Camera.h"

NS_FT_BEGIN

void ShaderNode::pre_draw(const Camera *camera) {
    current_shader_program_->use();
    current_shader_program_->updateUniforms(camera, this);
}

NS_FT_END