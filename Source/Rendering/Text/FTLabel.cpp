#include "FTLabel.h"
#include <Rendering/Shader/FTShaderCache.h>
#include <Rendering/Shader/FTFontShader.h>
#include "FTFontCache.h"

FTLabel::FTLabel(const std::basic_string<char>& fontpath, const std::basic_string<wchar_t>& text, int font_size, bool is_mutable) : FTIndexedTexturedMesh(), anchor_point_(0, 0), position_(0, 0), is_mutable_(is_mutable), font_size_(font_size) {

    font_ = FTFontCache::getSharedInstance()->getFont(fontpath);

    auto data = font_->generateMeshForString(text, font_size, label_size_);

    auto texture = font_->getTexture();

    setTexture(texture);
    loadIndexedMeshData(data, !is_mutable);

    if (is_mutable)
        mesh_data_ = std::move(data);

    setPosition(glm::vec2(0, 0));

    text_ = text;
}


FTLabel::~FTLabel() {
    
}

void FTLabel::setPosition(const glm::vec2& pos) {
    position_ = pos;
    transform_->setPosition(glm::vec3(position_.x - label_size_.x * anchor_point_.x, position_.y - label_size_.y * anchor_point_.y, 0));
}

void FTLabel::setString(const wchar_t* text) {
    if (text_ == text)
        return;

    text_ = text;

    FTAssert(is_mutable_, "Trying to change immutable FTLabel!");

    mesh_data_->getIndices().clear();
    mesh_data_->getVertices().clear();

    font_->populateMeshDataForString(mesh_data_, text, font_size_, label_size_);
    setIndexedMeshData(mesh_data_);

    setPosition(position_);
}
