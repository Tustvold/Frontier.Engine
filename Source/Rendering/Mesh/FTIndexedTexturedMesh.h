#pragma once
#include <Rendering/Shader/FTVertexTextureShaderProgram.h>
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Textures/FTTexture.h>

template <typename VertexType, typename IndexType>
class FTIndexedTexturedMesh : public FTIndexedMesh<VertexType, IndexType> {
public:
	explicit FTIndexedTexturedMesh(FTTransform* transform, FTVertexTextureShaderProgram* shader_program) : FTIndexedMesh(transform, shader_program), texture_(nullptr) {
	}

	virtual ~FTIndexedTexturedMesh() {
		texture_->release();
	}

	void setTexture(FTTexture* texture) {
		if (texture_ != nullptr)
			texture_->release();
		texture_ = texture;
		texture_->retain();
	}

	void draw() override {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_->getTextureId());
		glUniform1i(((FTVertexTextureShaderProgram*)shader_program_)->getTextureUniformId(), 0);
		FTIndexedMesh::draw();
	}

protected:
	GLuint uv_buffer_id_;
	FTTexture* texture_;
};
