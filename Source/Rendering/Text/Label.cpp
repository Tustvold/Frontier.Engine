#include "Label.h"
#include <Rendering/Shader/ShaderCache.h>
#include <Engine.h>
#include "FontCache.h"
#include <Util/StringUtils.h>

NS_FT_BEGIN

Label::Label(const std::wstring &text, int font_size, bool is_mutable, const std::string &style,
                 FontShader *shader) :
        IndexedMesh(shader),
        font_(nullptr),
        is_mutable_(is_mutable),
        font_size_(font_size),
        string_dirty_(false) {

    load(style, text);
}

Label::Label(const std::string &text, int font_size, bool is_mutable, const std::string &style,
                 FontShader *shader) :
        IndexedMesh(shader),
        font_(nullptr),
        is_mutable_(is_mutable),
        font_size_(font_size),
        string_dirty_(false) {

    load(style, WCharUtil::convertString(text));
}

void Label::setStyle(const std::string &style) {
    auto ret = Engine::getDirector()->getFontCache()->getFontStyle(style);

    if (font_ != ret.first) {
        FTAssert(is_mutable_, "Cannot change font of non-mutable string");
        font_ = ret.first;
        string_dirty_ = true;
    }
    material_ = *ret.second;
}

void Label::load(const std::string &style, const std::wstring &text) {
    auto ret = Engine::getDirector()->getFontCache()->getFontStyle(style);

    font_ = ret.first;
    material_ = *ret.second;

    mesh_data_ = font_->generateMeshForString(text, font_size_);

    loadIndexedMeshData(mesh_data_.get(), !is_mutable_);

    text_ = text;
}


Label::~Label() {

}

void Label::pre_draw(const Camera *camera) {
    updateMesh();

    FTLabelBase_::pre_draw(camera);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void Label::post_draw() {
    FTLabelBase_::post_draw();
    glDisable(GL_BLEND);
}

void Label::setString(const std::wstring &text) {
    if (text_ == text)
        return;

    FTAssert(is_mutable_, "Trying to change immutable Label!");

    text_ = text;
    string_dirty_ = true;
}

const std::shared_ptr<FontMeshData> &Label::getMeshData() {
    updateMesh();
    return mesh_data_;
}

void Label::updateMesh() {
    if (string_dirty_) {
        mesh_data_->clear();

        font_->populateMeshDataForString(mesh_data_.get(), text_, font_size_);
        setIndexedMeshData(mesh_data_.get());
    }
}

NS_FT_END