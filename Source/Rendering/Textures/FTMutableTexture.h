#pragma once

#include <Frontier.h>
#include "FTTexture.h"

class FTMutableTexture : public FTTexture {
public:
    

    FTMutableTexture();

    virtual ~FTMutableTexture();

    void setPixels(GLuint* pixels, GLuint width, GLuint height);

    GLuint getTextureId() override {
        return texture_id_;
    }

    virtual size_t getWidth() const override {
        return width_;
    }

    virtual size_t getHeight() const override {
        return height_;
    }

protected:

    GLuint texture_id_;
    unsigned int width_;
    unsigned int height_;
};
