#pragma once
#include <Rendering/Shader/FTVertexTextureShaderProgram.h>
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Textures/FTTexture.h>

template <typename Transform, typename ShaderProgram, typename VertexType, typename IndexType>
class FTIndexedTexturedMesh : public FTIndexedMesh<Transform, ShaderProgram, VertexType, IndexType> {
public:
	explicit FTIndexedTexturedMesh() : FTIndexedMesh() {

	}

	virtual ~FTIndexedTexturedMesh() {

	}

	void setTexture(std::shared_ptr<FTTexture> texture) {
		texture_ = texture;
	}

	void draw() override {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_->getTextureId());
		glUniform1i(((FTVertexTextureShaderProgram*)shader_program_.get())->getTextureUniformId(), 0);
		FTIndexedMesh::draw();
	}

protected:
	GLuint uv_buffer_id_;
	std::shared_ptr<FTTexture> texture_;
};
