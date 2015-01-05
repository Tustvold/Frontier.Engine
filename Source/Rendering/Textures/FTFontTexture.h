#pragma once
#include "FTTexture.h"

struct texture_atlas_t;

class FTFontTexture : public FTTexture {
public:
	explicit FTFontTexture(texture_atlas_t* texture_atlas);
	~FTFontTexture();

	GLuint getTextureId() override;

	texture_atlas_t* getTextureAtlas() {
		return texture_atlas_;
	}

protected:
	texture_atlas_t* texture_atlas_;
};
