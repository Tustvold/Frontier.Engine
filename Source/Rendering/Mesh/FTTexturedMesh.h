#pragma once
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Textures/FTTexture.h>
#include <Rendering/Shader/FTVertexTextureShaderProgram.h>

template <typename VertexType, typename IndexType>
class FTTexturedMesh : public FTMesh<VertexType> {
private:
    typedef FTMesh<VertexType> FTTexturedMeshBase_;

public:
    explicit FTTexturedMesh(FTVertexTextureShaderProgram* shader = FTShaderNode::getShaderUtil<FTVertexTextureShaderProgram>()) : 
        FTTexturedMeshBase_(shader) {

    }

    virtual ~FTTexturedMesh() {

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
        glUniform1i(((FTVertexTextureShaderProgram*)FTTexturedMeshBase_::current_shader_program_)->getTextureUniformId(), 0);
        FTTexturedMeshBase_::draw();
    }

protected:
    std::shared_ptr<FTTexture> texture_;
};
