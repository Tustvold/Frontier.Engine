#pragma once
#include <Rendering/FTDrawable.h>
#include <Rendering/Camera/FTCamera.h>
#include <Rendering/Shader/FTVertexShaderProgram.h>
#include <Rendering/Scene/Transform/FTTransform.h>

// The base class of everything within the scene heirarchy
// Manages a shader program which it populates with the camera data
class FTNode : public FTDrawable {
public:

	explicit FTNode(FTTransform* transform, FTVertexShaderProgram* shader_program) : transform_(transform), shader_program_(shader_program) {
		shader_program_->retain();
		transform_->retain();
	}

	~FTNode() {
		shader_program_->release();
		transform_->release();
	}

	virtual void pre_draw() = 0;
	virtual void post_draw() = 0;

	// Override to provide custom transforms, frustrum culling, children, etc
	virtual void visit(const FTCamera* camera) {
		transform_->updateMatrices();
		glm::mat4 mvp = camera->getViewProjectionMatrix() * transform_->getTransformMatrix();
		shader_program_->use();
		shader_program_->updateMvpUniforms(&mvp[0][0]);
		this->pre_draw();
		this->draw();
		this->post_draw();
		shader_program_->cleanup();
	}

protected:
	FTTransform* transform_;
	FTVertexShaderProgram* shader_program_;
};
