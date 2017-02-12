#pragma once
#include <Rendering/Mesh/FTIndexedMesh.h>
#include <Rendering/Texture/FTTexture.h>
#include <Rendering/Shader/FTVertexShaderProgramLighting.h>
#include <Rendering/FTView.h>

template <typename VertexType, typename IndexType>
class FTLightingMesh : public FTIndexedMesh<VertexType, IndexType> {
private:
    typedef FTIndexedMesh<VertexType, IndexType> FTLightingMeshBase_;

public:
    explicit FTLightingMesh(FTVertexShaderProgramLighting* shader = FTShaderNode::getShaderUtil<FTVertexShaderProgramLighting>()) :
        FTLightingMeshBase_(shader) {

    }

    virtual ~FTLightingMesh() {

    }

    void setTexture(const std::shared_ptr<FTTexture>& texture) {
        texture_ = texture;
    }

    void setTexture(std::shared_ptr<FTTexture>&& texture) {
        texture_ = std::move(texture);
    }

protected:
    std::shared_ptr<FTTexture> texture_;
};
