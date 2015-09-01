#pragma once
#include <FTObject.h>
#include <GL/glew.h>

// TODO Implement system for using multiple texture units
class FTTexture : public FTObject {
public:

	virtual GLuint getTextureId() = 0;

	~FTTexture() {

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
	FTTexture() {

	}



	unsigned int width_;
	unsigned int height_;
	unsigned int mipmap_count_;
};
