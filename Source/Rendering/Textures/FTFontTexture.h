#pragma once
#include "FTTexture.h"

namespace ftgl
{
    struct texture_atlas_t;
}

class FTFontTexture : public FTTexture {
public:
    explicit FTFontTexture(ftgl::texture_atlas_t* texture_atlas);
    ~FTFontTexture();

    GLuint getTextureId() override;

    ftgl::texture_atlas_t* getTextureAtlas() {
        return texture_atlas_;
    }

protected:
    ftgl::texture_atlas_t* texture_atlas_;
};
