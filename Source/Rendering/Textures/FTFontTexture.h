#pragma once
#include "FTTexture.h"
#include <texture-atlas.h>

namespace ftgl
{
    struct texture_atlas_t;
}

class FTFontTexture : public FTTexture {
public:
    ;
    explicit FTFontTexture(ftgl::texture_atlas_t* texture_atlas);
    ~FTFontTexture();

    GLuint getTextureId() override;

    ftgl::texture_atlas_t* getTextureAtlas() const {
        return texture_atlas_;
    }

    virtual size_t getWidth() const override {
        return texture_atlas_->width;
    }

    virtual size_t getHeight() const override {
        return texture_atlas_->height;
    }

protected:
    ftgl::texture_atlas_t* texture_atlas_;
};
