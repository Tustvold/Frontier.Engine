#include "FTLabel.h"
#include <Rendering/Shader/FTShaderCache.h>
#include <Rendering/Scene/Transform/FTTransformPosition.h>
#include <Rendering/Shader/FTFontShader.h>
#include "FTFontCache.h"

FTLabel::FTLabel(const char* fontpath, const wchar_t* text) : FTIndexedTexturedMesh(new FTTransformPosition(), FTShaderCache::getSharedInstance()->getShaderProgram<FTFontShader>()) {
	transform_->release();

	FTFont* font = FTFontCache::getSharedInstance()->getFont("Fonts/Vera.ttf");

	auto data = font->generateMeshForString(text, 32, label_size_);

	FTTexture* texture = font->getTexture();

	setTexture(texture);
	loadIndexedMeshData(data);

	data->release();

	setPosition(glm::vec2(0, 0));
}

FTLabel::~FTLabel() {
}

void FTLabel::setPosition(const glm::vec2& pos) {
	((FTTransformPosition*)transform_)->setPosition(glm::vec3(pos.x-label_size_.x/2.0f, pos.y-label_size_.y/2.0f, 0));
}