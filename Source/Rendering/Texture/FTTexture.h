#pragma once
#include <Frontier.h>

NS_FT_BEGIN

// TODO Implement system for using multiple texture units
class FTTexture {
public:

    virtual GLuint getTextureId() = 0;

    virtual ~FTTexture() {

    }

    virtual size_t getWidth() const = 0;

    virtual size_t getHeight() const = 0;

    unsigned int getMipMapCount() const {
        return mipmap_count_;
    }

protected:
    FTTexture() : mipmap_count_(1) {

    }

    unsigned int mipmap_count_;
};

NS_FT_END