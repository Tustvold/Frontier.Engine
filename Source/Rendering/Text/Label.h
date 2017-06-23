#pragma once
#include <Rendering/Node.h>
#include <Rendering/Mesh/IndexedMesh.h>
#include "Font.h"
#include <Rendering/Shader/FontShader.h>

NS_FT_BEGIN

class Label : public IndexedMesh<VertexTexture<glm::vec2>, uint16_t> {
private:
    typedef IndexedMesh<VertexTexture<glm::vec2>, uint16_t> FTLabelBase_;
public:
    
    Label(const std::wstring& text, int font_size, bool is_mutable = false, const std::string& style = "DefaultText", FontShader* shader = ShaderNode::getShaderUtil<FontShader>());
    Label(const std::string& text, int font_size, bool is_mutable = false, const std::string& style = "DefaultText", FontShader* shader = ShaderNode::getShaderUtil<FontShader>());
    virtual ~Label();

    void setString(const std::wstring& text);

    void pre_draw(const Camera* camera) override;

    void post_draw() override;

    int getFontSize() const {
        return font_size_;
    }

    const std::shared_ptr<FontMeshData>& getMeshData();

    void setStyle(const std::string& style);

protected:
    std::shared_ptr<FontMeshData> mesh_data_;
    Font* font_;
    std::wstring text_;

    bool is_mutable_;
    int font_size_;
    bool string_dirty_;

private:
    void load(const std::string& style, const std::wstring& text);

    void updateMesh();
};

NS_FT_END