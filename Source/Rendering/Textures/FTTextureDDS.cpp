﻿#include "FTTextureDDS.h"

FTTextureDDS::FTTextureDDS(const std::basic_string<char>& filename) {
	texture_id_ = loadDDS(filename);
}

FTTextureDDS::~FTTextureDDS() {
	glDeleteTextures(1, &texture_id_);
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

// Code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
GLuint FTTextureDDS::loadDDS(const std::basic_string<char>& imagepath) {
	unsigned char header[124];

	FILE* fp;

	/* try to open the file */
	auto err = fopen_s(&fp, imagepath.c_str(), "rb");
	if (err != 0) {
		FTLogError("%s could not be opened!", imagepath);
		getchar();
		return 0;
	}

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp);

	height_ = *(unsigned int*)&(header[8]);
	width_ = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	mipmap_count_ = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);


	unsigned char* buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipmap_count_ > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC) {
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			free(buffer);
			return 0;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipmap_count_ && (width_ || height_); ++level) {
		unsigned int size = ((width_ + 3) / 4) * ((height_ + 3) / 4) * blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width_, height_,
		                                    0, size, buffer + offset);

		offset += size;
		width_ /= 2;
		height_ /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if (width_ < 1)
			width_ = 1;
		if (height_ < 1)
			height_ = 1;

	}

	free(buffer);

	return textureID;
}
