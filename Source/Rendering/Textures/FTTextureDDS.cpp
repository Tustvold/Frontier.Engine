#include "FTTextureDDS.h"
#include <FTEngine.h>
#include <Util/FTFileManager.h>

#include <string.h> // for strncmp

FTTextureDDS::FTTextureDDS(const std::string& filename) : width_(0), height_(0) {
    texture_id_ = loadDDS(filename);
}

FTTextureDDS::~FTTextureDDS() {
    glDeleteTextures(1, &texture_id_);
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

/* HACK: no fopen_s on non-Windows systems */
#ifndef WIN32
#   define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
#endif

// Code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
GLuint FTTextureDDS::loadDDS(const std::string& provided_path) {
    unsigned char header[124];

    auto imagepath = FTEngine::getFileManager()->getPathToFile(provided_path);
    FTAssert(imagepath != "", "File %s not found", provided_path.c_str());

    FILE* fp;

    /* try to open the file */
    auto err = fopen_s(&fp, imagepath.c_str(), "rb");
    FTAssert(err == 0, "File %s could not be opened!", imagepath.c_str());


    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        FTAssert(false, "Not a DDS texture");
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp);

    height_ = *(unsigned int*)&(header[8]);
    width_ = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    mipmap_count_ = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);


    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipmap_count_ > 1 ? linearSize * 2 : linearSize;
    unsigned char* buffer = new unsigned char[bufsize];
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

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
