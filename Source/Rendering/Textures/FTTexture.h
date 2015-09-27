#pragma once
#include <Frontier.h>

// TODO Implement system for using multiple texture units
class FTTexture {
public:

    virtual GLuint getTextureId() = 0;

    virtual ~FTTexture() {

    }

    unsigned int getWidth() const {
        return width_;
    }

    unsigned int getHeight() const {
        return height_;
    }

    unsigned int getMipMapCount() const {
        return mipmap_count_;
    }

protected:
    FTTexture() : width_(0), height_(0), mipmap_count_(1) {

    }


    unsigned int width_;
    unsigned int height_;
    unsigned int mipmap_count_;
};
