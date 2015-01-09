#include "FTLabel.h"
#include <Rendering/Shader/FTShaderCache.h>
#include <Rendering/Shader/FTFontShader.h>
#include "FTFontCache.h"

FTLabel::FTLabel(const char* fontpath, const wchar_t* text, int font_size, bool is_mutable) : FTIndexedTexturedMesh(FTShaderCache::getSharedInstance()->getShaderProgram<FTFontShader>()), anchor_point_(0, 0), position_(0, 0), transform_(new FTTransformPosition()), is_mutable_(is_mutable), font_size_(font_size) {

	FTFont* font = FTFontCache::getSharedInstance()->getFont("Fonts/Vera.ttf");

	auto data = font->generateMeshForString(text, font_size, label_size_);

	FTTexture* texture = font->getTexture();

	setTexture(texture);
	loadIndexedMeshData(data, !is_mutable);

	data->release();

	setPosition(glm::vec2(0, 0));
}

FTLabel::~FTLabel() {
	transform_->release();
}

void FTLabel::setPosition(const glm::vec2& pos) {
	position_ = pos;
	transform_->setPosition(glm::vec3(position_.x - label_size_.x * anchor_point_.x, position_.y - label_size_.y * anchor_point_.y, 0));
}

void FTLabel::setString(const wchar_t* text) {
	FTAssert(is_mutable_, "Trying to change immutable FTLabel!");
	FTFont* font = FTFontCache::getSharedInstance()->getFont("Fonts/Vera.ttf");

	auto data = font->generateMeshForString(text, font_size_, label_size_);
	setIndexedMeshData(data);
	data->release();

	setPosition(position_);
}
