#include "freetype-gl.h"
#include "FontTexture.h"

NS_FT_BEGIN

FontTexture::FontTexture(ftgl::texture_atlas_t* texture_atlas) : texture_atlas_(texture_atlas) {
    texture_atlas_->id = 0;
}

FontTexture::~FontTexture() {
    texture_atlas_delete(texture_atlas_);
}

size_t FontTexture::getWidth() const {
    return texture_atlas_->width;
}

size_t FontTexture::getHeight() const {
    return texture_atlas_->height;
}

GLuint FontTexture::getTextureId() {
    return texture_atlas_->id;
}

void FontTexture::flushData() {
    if (texture_atlas_->id == 0)
        glGenTextures(1, &texture_atlas_->id);

    glBindTexture(GL_TEXTURE_2D, texture_atlas_->id);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, texture_atlas_->width, texture_atlas_->height,
        0, GL_RED, GL_UNSIGNED_BYTE, texture_atlas_->data);
}

NS_FT_END