#pragma once
#include "Texture.h"
#include "Frontier.h"

NS_FT_BEGIN

class TextureDDS : public Texture {
public:
    

    explicit TextureDDS(const std::string& filename);
    virtual ~TextureDDS();

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
private:
    GLuint loadDDS(const std::string& filename);
};

NS_FT_END