#pragma once
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Textures/FTTexture.h>

template <typename ShaderProgram, typename VertexType, typename IndexType>
class FTIndexedTexturedMesh : public FTIndexedMesh<ShaderProgram, VertexType, IndexType> {
private:
    typedef FTIndexedMesh<ShaderProgram, VertexType, IndexType> FTIndexedMeshBase_;

public:
    FTIndexedTexturedMesh() : FTIndexedMeshBase_() {

    }

    virtual ~FTIndexedTexturedMesh() {

    }

    void setTexture(std::shared_ptr<FTTexture> texture) {
        texture_ = texture;
    }

    void draw() override {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_->getTextureId());
        glUniform1i(this->current_shader_program_->getTextureUniformId(), 0);
        FTIndexedMeshBase_::draw();
    }

protected:
    std::shared_ptr<FTTexture> texture_;
};
