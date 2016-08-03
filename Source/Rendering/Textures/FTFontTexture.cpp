#include "freetype-gl.h"
#include "FTFontTexture.h"


FTFontTexture::FTFontTexture(ftgl::texture_atlas_t* texture_atlas) : texture_atlas_(texture_atlas) {
    glGenTextures(1, &texture_atlas_->id);
    glBindTexture(GL_TEXTURE_2D, texture_atlas_->id);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

FTFontTexture::~FTFontTexture() {
    texture_atlas_delete(texture_atlas_);
}

size_t FTFontTexture::getWidth() const {
    return texture_atlas_->width;
}

size_t FTFontTexture::getHeight() const {
    return texture_atlas_->height;
}

GLuint FTFontTexture::getTextureId() {
    return texture_atlas_->id;
}

void FTFontTexture::flushData() {
    glBindTexture(GL_TEXTURE_2D, texture_atlas_->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, texture_atlas_->width, texture_atlas_->height,
        0, GL_RED, GL_UNSIGNED_BYTE, texture_atlas_->data);
}