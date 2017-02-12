#pragma once
#include <Rendering/FTNode.h>
#include <Rendering/Mesh/FTIndexedMesh.h>
#include "FTFont.h"
#include <Rendering/Shader/FTFontShader.h>

class FTLabel : public FTIndexedMesh<FTVertexTexture<glm::vec2>, uint16_t> {
private:
    typedef FTIndexedMesh<FTVertexTexture<glm::vec2>, uint16_t> FTLabelBase_;
public:
    
    FTLabel(const std::wstring& text, int font_size, bool is_mutable = false, const std::string& style = "DefaultText", FTFontShader* shader = FTShaderNode::getShaderUtil<FTFontShader>());
    FTLabel(const std::string& text, int font_size, bool is_mutable = false, const std::string& style = "DefaultText", FTFontShader* shader = FTShaderNode::getShaderUtil<FTFontShader>());
    virtual ~FTLabel();

    void setString(const std::wstring& text);

    void pre_draw(const FTCamera* camera) override;

    void post_draw() override;

    int getFontSize() const {
        return font_size_;
    }

    const std::shared_ptr<FTFontMeshData>& getMeshData() const {
        return mesh_data_;
    }

    void setStyle(const std::string& style);

protected:
    std::shared_ptr<FTFontMeshData> mesh_data_;
    FTFont* font_;
    std::wstring text_;

    bool is_mutable_;
    int font_size_;
    bool string_dirty_;

private:
    void load(const std::string& style, const std::wstring& text);
};
