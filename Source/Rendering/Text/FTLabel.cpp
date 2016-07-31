#include "FTLabel.h"
#include <Rendering/Shader/FTShaderCache.h>
#include <FTEngine.h>
#include "FTFontCache.h"
#include <Util/FTStringUtils.h>

FTLabel::FTLabel(const std::string& fontpath, const std::wstring& text, int font_size, bool is_mutable, FTFontShader* shader) : 
    FTIndexedTexturedMesh(shader),
    is_mutable_(is_mutable),
    font_size_(font_size) {

    load(fontpath, text);
}

FTLabel::FTLabel(const std::string& fontpath, const std::string& text, int font_size, bool is_mutable, FTFontShader* shader) :
FTIndexedTexturedMesh(shader),
is_mutable_(is_mutable),
font_size_(font_size) {

    load(fontpath, FTWCharUtil::convertString(text));
}

void FTLabel::load(const std::string& fontpath, const std::wstring& text) {
    font_ = FTEngine::getDirector()->getFontCache()->getFont(fontpath);

    mesh_data_ = font_->generateMeshForString(text, font_size_);

    auto texture = font_->getTexture();

    setTexture(texture);
    loadIndexedMeshData(mesh_data_.get(), !is_mutable_);

    text_ = text;
}


FTLabel::~FTLabel() {

}

void FTLabel::pre_draw(const glm::mat4& mvp) {
    FTLabelBase_::pre_draw(mvp);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    auto shader = (FTFontShader*)current_shader_program_;
    glUniform3f(shader->getFillColorUniformID(), fill_color_.x, fill_color_.y, fill_color_.z);

}

void FTLabel::post_draw() {
    FTLabelBase_::post_draw();
    glDisable(GL_BLEND);
}

void FTLabel::setString(const std::wstring& text) {
    if (text_ == text)
        return;

    FTAssert(is_mutable_, "Trying to change immutable FTLabel!");

    text_ = text;

    mesh_data_->clear();

    font_->populateMeshDataForString(mesh_data_.get(), text, font_size_);
    setIndexedMeshData(mesh_data_.get());
}
