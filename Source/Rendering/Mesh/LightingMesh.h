#pragma once
#include <Rendering/Mesh/IndexedMesh.h>
#include <Rendering/Texture/Texture.h>
#include <Rendering/Shader/VertexShaderProgramLighting.h>
#include <Rendering/View.h>

NS_FT_BEGIN

template <typename VertexType, typename IndexType>
class LightingMesh : public IndexedMesh<VertexType, IndexType> {
private:
    typedef IndexedMesh<VertexType, IndexType> FTLightingMeshBase_;

public:
    explicit LightingMesh(VertexShaderProgramLighting* shader = ShaderNode::getShaderUtil<VertexShaderProgramLighting>()) :
        FTLightingMeshBase_(shader) {

    }

    virtual ~LightingMesh() {

    }

    void setTexture(const std::shared_ptr<Texture>& texture) {
        texture_ = texture;
    }

    void setTexture(std::shared_ptr<Texture>&& texture) {
        texture_ = std::move(texture);
    }

protected:
    std::shared_ptr<Texture> texture_;
};

NS_FT_END