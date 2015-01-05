#pragma once
#include "FTTexture.h"

class FTTextureDDS : public FTTexture {
public:
	
	explicit FTTextureDDS(const char* filename);
	virtual ~FTTextureDDS();

	GLuint getTextureId() override {
		return texture_id_;
	}

protected:
	GLuint texture_id_;
private:
	GLuint loadDDS(const char* filename);
};
