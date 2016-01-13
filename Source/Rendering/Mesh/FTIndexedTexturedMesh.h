#pragma once
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Textures/FTTexture.h>
#include <Rendering/Shader/FTVertexTextureShaderProgram.h>

template <typename VertexType, typename IndexType>
class FTIndexedTexturedMesh : public FTIndexedMesh<VertexType, IndexType> {
private:
    typedef FTIndexedMesh<VertexType, IndexType> FTIndexedTexturedMeshBase_;

public:
    explicit FTIndexedTexturedMesh(FTVertexTextureShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexTextureShaderProgram>()) : 
        FTIndexedTexturedMeshBase_(shader) {

    }

    virtual ~FTIndexedTexturedMesh() {

    }

    void setTexture(const std::shared_ptr<FTTexture>& texture) {
        texture_ = texture;
    }

    void setTexture(std::shared_ptr<FTTexture>&& texture) {
        texture_ = std::move(texture);
    }

    void draw() override {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_->getTextureId());
        glUniform1i(((FTVertexTextureShaderProgram*)FTIndexedTexturedMeshBase_::current_shader_program_)->getTextureUniformId(), 0);
        FTIndexedTexturedMeshBase_::draw();
    }

protected:
    std::shared_ptr<FTTexture> texture_;
};
