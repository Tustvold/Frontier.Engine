#pragma once
#include <Rendering/FTNode.h>
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>
#include "FTFont.h"
#include <Rendering/Shader/FTFontShader.h>

class FTLabel : public FTIndexedTexturedMesh<FTVertexColorTexture<glm::vec2>, uint16_t> {
private:
    typedef FTIndexedTexturedMesh<FTVertexColorTexture<glm::vec2>, uint16_t> FTLabelBase_;
public:
    
    FTLabel(const std::string& fontpath, const std::wstring& text, int font_size, bool is_mutable = false, FTFontShader* shader = FTShaderNode::getShaderUtil<FTFontShader>());
    FTLabel(const std::string& fontpath, const std::string& text, int font_size, bool is_mutable = false, FTFontShader* shader = FTShaderNode::getShaderUtil<FTFontShader>());
    virtual ~FTLabel();

    void setString(const wchar_t* text);

    void pre_draw(const glm::mat4& mvp) override;

    void post_draw() override;

protected:
    std::shared_ptr<FTIndexedMeshData<FTVertexColorTexture<glm::vec2>, uint16_t>> mesh_data_;
    std::shared_ptr<FTFont> font_;
    std::basic_string<wchar_t> text_;

    bool is_mutable_;
    int font_size_;

private:
    void load(const std::string& fontpath, const std::wstring& text);
};
