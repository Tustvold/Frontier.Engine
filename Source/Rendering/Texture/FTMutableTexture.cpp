#include "FTMutableTexture.h"

FTMutableTexture::FTMutableTexture() : width_(0), height_(0) {
    mipmap_count_ = 1;

    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

FTMutableTexture::~FTMutableTexture() {
    glDeleteTextures(1, &texture_id_);
    texture_id_ = 0;
    width_ = 0;
    height_ = 0;
}

void FTMutableTexture::setPixels(glm::tvec4<uint8_t>* pixels, GLuint width, GLuint height) {
    width_ = width;
    height_ = height;
    
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    GLenum error = glGetError(); 
    FTAssert(error == GL_NO_ERROR, "Error setting texture pixels: %i", error);
}
