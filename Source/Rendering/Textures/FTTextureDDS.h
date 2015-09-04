#pragma once
#include "FTTexture.h"
#include "Frontier.h"

class FTTextureDDS : public FTTexture {
public:

    explicit FTTextureDDS(const std::basic_string<char>& filename);
    virtual ~FTTextureDDS();

    GLuint getTextureId() override {
        return texture_id_;
    }

protected:
    GLuint texture_id_;
private:
    GLuint loadDDS(const std::basic_string<char>& filename);
};
