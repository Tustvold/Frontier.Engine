#include "TextureDDS.h"
#include <Engine.h>
#include <IO/FileManager.h>

#include <string.h> // for strncmp

NS_FT_BEGIN

TextureDDS::TextureDDS(const std::string& filename) : width_(0), height_(0) {
    texture_id_ = loadDDS(filename);
}

TextureDDS::~TextureDDS() {
    glDeleteTextures(1, &texture_id_);
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint TextureDDS::loadDDS(const std::string& provided_path) {
    uint32_t header[124 / sizeof(uint32_t)];

    auto file = Engine::getFileManager()->getFile(provided_path);

    FTAssert(file && file->open("rb"), "File %s could not be opened!", provided_path.c_str());

    /* verify the type of file */
    char filecode[4];
    FTAssert(file->read(filecode, 4) == 4, "Read Error");
    if (strncmp(filecode, "DDS ", 4) != 0) {
        file->close();
        FTAssert(false, "Not a DDS texture");
        return 0;
    }

    /* get the surface desc */
    FTAssert(file->read(&header, 124) == 124, "Read Error");

    height_ = header[8 / sizeof(uint32_t)];
    width_ = header[12 / sizeof(uint32_t)];
    unsigned int linearSize = header[16 / sizeof(uint32_t)];
    mipmap_count_ = header[24 / sizeof(uint32_t)];
    unsigned int fourCC = header[80 / sizeof(uint32_t)];


    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipmap_count_ > 1 ? linearSize * 2 : linearSize;
    unsigned char* buffer = new unsigned char[bufsize];
    FTAssert(file->read(buffer, bufsize) == bufsize, "Read Error");

    file->close();

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
            delete[] buffer;
            FTAssert(false, "File read error");
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

    int height = height_;
    int width = width_;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipmap_count_ && (width || height); ++level) {
        unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                                            0, size, buffer + offset);

        offset += size;
        width /= 2;
        height /= 2;

        if (width < 1)
            width = 1;
        if (height < 1)
            height = 1;

    }

    delete[] buffer;

    return textureID;
}

NS_FT_END
