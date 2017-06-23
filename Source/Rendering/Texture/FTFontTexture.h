#pragma once
#include "FTTexture.h"

namespace ftgl
{
    struct texture_atlas_t;
}

NS_FT_BEGIN

class FTFontTexture : public FTTexture {
public:
    explicit FTFontTexture(ftgl::texture_atlas_t* texture_atlas);
    ~FTFontTexture();

    GLuint getTextureId() override;

    ftgl::texture_atlas_t* getTextureAtlas() const {
        return texture_atlas_;
    }

    virtual size_t getWidth() const override;

    virtual size_t getHeight() const override;

    // Flush modified data to GPU
    void flushData();

protected:
    ftgl::texture_atlas_t* texture_atlas_;
};

NS_FT_END