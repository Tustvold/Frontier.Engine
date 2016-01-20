﻿#pragma once
#include <Rendering/FTNode.h>
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>
#include "FTFont.h"
#include <Rendering/Shader/FTFontShader.h>

class FTLabel : public FTIndexedTexturedMesh<FTVertexTexture<glm::vec2>, uint16_t> {
private:
    typedef FTIndexedTexturedMesh<FTVertexTexture<glm::vec2>, uint16_t> FTLabelBase_;
public:
    
    FTLabel(const std::string& fontpath, const std::wstring& text, int font_size, bool is_mutable = false, FTFontShader* shader = FTShaderNode::getShaderUtil<FTFontShader>());
    FTLabel(const std::string& fontpath, const std::string& text, int font_size, bool is_mutable = false, FTFontShader* shader = FTShaderNode::getShaderUtil<FTFontShader>());
    virtual ~FTLabel();

    void setString(const std::wstring& text);

    void pre_draw(const glm::mat4& mvp) override;

    void post_draw() override;

    void setFillColor(const glm::vec3& color) {
        fill_color_ = color;
    }

    int getFontSize() const {
        return font_size_;
    }

    const std::shared_ptr<FTFontMeshData>& getMeshData() const {
        return mesh_data_;
    }

protected:
    std::shared_ptr<FTFontMeshData> mesh_data_;
    std::shared_ptr<FTFont> font_;
    std::wstring text_;

    glm::vec3 fill_color_;
    bool is_mutable_;
    int font_size_;

private:
    void load(const std::string& fontpath, const std::wstring& text);
};
