#include "FTFontTexture.h"
#include "freetype-gl.h"

FTFontTexture::FTFontTexture(ftgl::texture_atlas_t* texture_atlas) : texture_atlas_(texture_atlas) {
}

FTFontTexture::~FTFontTexture() {
    texture_atlas_delete(texture_atlas_);
}

GLuint FTFontTexture::getTextureId() {
    return texture_atlas_->id;
}
