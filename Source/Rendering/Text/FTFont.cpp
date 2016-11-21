#include "FTFont.h"
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>
#include <Util/FTFileManager.h>
#include "freetype-gl.h"
#include "distance-field.h"
#include "vertex-buffer.h"
#include "shader.h"
#include "mat4.h"
#include "texture-font.h"
#include "texture-atlas.h"
#include "platform.h"
#include "utf8-utils.h"

#include <ft2build.h>
#include <stdlib.h>
#include <sstream>
#include FT_FREETYPE_H
#include "FTFontUtils.h"

FTFont::FTFont(const std::string& filename, const char* cache) : font_texture_(nullptr) {
    auto path = FTEngine::getFileManager()->getPathToFile(filename);
    FTAssert(path != "", "Font doesn't exist at path");

    auto extension = path.substr(path.find_last_of(".") + 1);

    if (extension == "ttf") {
        font_texture_ = std::make_shared<FTFontTexture>(texture_atlas_new(1024, 1024, 1));
        font_ = texture_font_new_from_file(font_texture_->getTextureAtlas(), getPointSize(), path.c_str());


        const char* iter = cache;
        while (*iter) {
            add_glyph(iter);
            iter++;
        }
    } else if (extension == "ftfont") {
        FILE *fr = fopen(path.c_str(), "r");
        auto readBuffer = CompressionBuffer::readFile(fr);
        fclose(fr);

        auto tag = std::make_unique<Tag>(readBuffer.get());

        font_ = FTFontUtils::createFontForTag(tag.get());
        font_texture_ = std::make_shared<FTFontTexture>(font_->atlas);
    } else {
        FTAssert(false, "Unrecognised extension");
    }


}

FTFont::~FTFont() {
    texture_font_delete(font_);
}

std::unique_ptr<FTFontMeshData> FTFont::generateMeshForString(const std::basic_string<wchar_t>& text, float point_size) {
    size_t length = text.length();
    auto data = new FTFontMeshData(4 * length, 6 * length);
    populateMeshDataForString(data, text, point_size);
    return std::unique_ptr<FTFontMeshData>(data);
}

// Code from freetype-gl demo
// ------------------------------------------------------ MitchellNetravali ---
// Mitchell Netravali reconstruction filter
static float MitchellNetravali( float x ) {
    const float B = 1/3.0, C = 1/3.0; // Recommended
    // const float B =   1.0, C =   0.0; // Cubic B-spline (smoother results)
    // const float B =   0.0, C = 1/2.0; // Catmull-Rom spline (sharper results)
    x = fabs(x);
    if( x < 1 )
        return ( ( 12 -  9 * B - 6 * C) * x * x * x
                 + (-18 + 12 * B + 6 * C) * x * x
                 + (  6 -  2 * B) ) / 6;
    else if( x < 2 )
        return ( (     -B -  6 * C) * x * x * x
                 + (  6 * B + 30 * C) * x * x
                 + (-12 * B - 48 * C) * x
                 + (  8 * B + 24 * C) ) / 6;
    else
        return 0;
}


// ------------------------------------------------------------ interpolate ---
static float interpolate( float x, float y0, float y1, float y2, float y3 ) {
    float c0 = MitchellNetravali(x-1);
    float c1 = MitchellNetravali(x  );
    float c2 = MitchellNetravali(x+1);
    float c3 = MitchellNetravali(x+2);
    float r =  c0*y0 + c1*y1 + c2*y2 + c3*y3;
    return std::min( std::max( r, 0.0f ), 1.0f );
}


// ------------------------------------------------------------------ scale ---
static int resize( double *src_data, int src_width, int src_height,
        double *dst_data, int dst_width, int dst_height ) {
    if( (src_width == dst_width) && (src_height == dst_height) )
    {
        memcpy( dst_data, src_data, src_width*src_height*sizeof(double));
        return 0;
    }
    int i,j;
    float xscale = src_width / (float) dst_width;
    float yscale = src_height / (float) dst_height;
    for( j=0; j < dst_height; ++j )
    {
        for( i=0; i < dst_width; ++i )
        {
            int src_i = (int) floor( i * xscale );
            int src_j = (int) floor( j * yscale );
            int i0 = std::min( std::max( 0, src_i-1 ), src_width-1 );
            int i1 = std::min( std::max( 0, src_i   ), src_width-1 );
            int i2 = std::min( std::max( 0, src_i+1 ), src_width-1 );
            int i3 = std::min( std::max( 0, src_i+2 ), src_width-1 );
            int j0 = std::min( std::max( 0, src_j-1 ), src_height-1 );
            int j1 = std::min( std::max( 0, src_j   ), src_height-1 );
            int j2 = std::min( std::max( 0, src_j+1 ), src_height-1 );
            int j3 = std::min( std::max( 0, src_j+2 ), src_height-1 );
            float t0 = interpolate( i / (float) dst_width,
                                    src_data[j0*src_width+i0],
                                    src_data[j0*src_width+i1],
                                    src_data[j0*src_width+i2],
                                    src_data[j0*src_width+i3] );
            float t1 = interpolate( i / (float) dst_width,
                                    src_data[j1*src_width+i0],
                                    src_data[j1*src_width+i1],
                                    src_data[j1*src_width+i2],
                                    src_data[j1*src_width+i3] );
            float t2 = interpolate( i / (float) dst_width,
                                    src_data[j2*src_width+i0],
                                    src_data[j2*src_width+i1],
                                    src_data[j2*src_width+i2],
                                    src_data[j2*src_width+i3] );
            float t3 = interpolate( i / (float) dst_width,
                                    src_data[j3*src_width+i0],
                                    src_data[j3*src_width+i1],
                                    src_data[j3*src_width+i2],
                                    src_data[j3*src_width+i3] );
            float y =  interpolate( j / (float) dst_height, t0, t1, t2, t3 );
            dst_data[j*dst_width+i] = y;
        }
    }
    return 0;
}


void FTFont::add_glyph(const char *codepoint) {
    size_t i, j;
    FT_Library library;
    FT_Face face;
    ftgl::texture_atlas_t* atlas = font_texture_->getTextureAtlas();

    FT_Init_FreeType( &library );
    FT_New_Face( library, font_->filename, 0, &face );
    FT_Select_Charmap( face, FT_ENCODING_UNICODE );
    FT_UInt glyph_index = FT_Get_Char_Index( face, utf8_to_utf32( codepoint ) );

    // Render glyph at high resolution (highres_size points)
    FT_Set_Char_Size( face, getHighResSize()*64, 0, 72, 72 );
    FT_Load_Glyph( face, glyph_index,
                   FT_LOAD_RENDER | FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT);
    FT_GlyphSlot slot = face->glyph;
    FT_Bitmap bitmap = slot->bitmap;

    // Allocate high resolution buffer
    size_t highres_width  = bitmap.width + 2*getPadding()*getHighResSize();
    size_t highres_height = bitmap.rows + 2*getPadding()*getHighResSize();
    double * highres_data = new double[ highres_width*highres_height];
    memset( highres_data, 0, highres_width*highres_height*sizeof(double) );

    // Copy high resolution bitmap with padding and normalize values
    for( j=0; j < bitmap.rows; ++j )
    {
        for( i=0; i < bitmap.width; ++i )
        {
            int x = i + getPadding() * getHighResSize();
            int y = j + getPadding() * getHighResSize();
            highres_data[y*highres_width+x] = bitmap.buffer[j*bitmap.width+i]/255.0;
        }
    }

    highres_data = make_distance_mapd( highres_data, highres_width, highres_height );

    // Allocate low resolution buffer
    size_t lowres_width  = round(highres_width * getLowResSize()/getHighResSize());
    size_t lowres_height = round(highres_height * lowres_width/(float) highres_width);
    double * lowres_data = new double[lowres_width*lowres_height];
    memset( lowres_data, 0, lowres_width*lowres_height*sizeof(double) );

    // Scale down highres buffer into lowres buffer
    resize( highres_data, highres_width, highres_height,
            lowres_data,  lowres_width,  lowres_height );

    // Convert the (double *) lowres buffer into a (unsigned char *) buffer and
    // rescale values between 0 and 255.
    unsigned char * data = new unsigned char[lowres_width*lowres_height];
    for( j=0; j < lowres_height; ++j )
    {
        for( i=0; i < lowres_width; ++i )
        {
            double v = lowres_data[j*lowres_width+i];
            data[j*lowres_width+i] = (int) (255*(1-v));
        }
    }

    // Compute new glyph information from highres value
    float ratio = getLowResSize()/getHighResSize();
    size_t pitch  = lowres_width * sizeof( unsigned char );

    // Create glyph
    texture_glyph_t * glyph = texture_glyph_new( );
    glyph->offset_x = (int)round((slot->bitmap_left + getPadding()*highres_width) * ratio);
    glyph->offset_y = (int)round((slot->bitmap_top + getPadding()*highres_height) * ratio);
    glyph->width    = lowres_width;
    glyph->height   = lowres_height;
    glyph->codepoint = utf8_to_utf32( codepoint );

    ivec4 region = texture_atlas_get_region( atlas, glyph->width, glyph->height );

    texture_atlas_set_region( atlas, region.x, region.y, glyph->width, glyph->height, data, pitch );
    glyph->s0       = (region.x + glyph->width * getPadding())/(float)atlas->width;
    glyph->t0       = (region.y + glyph->height * getPadding())/(float)atlas->height;
    glyph->s1       = (region.x + glyph->width - glyph->width * getPadding())/(float)atlas->width;
    glyph->t1       = (region.y + glyph->height - glyph->height * getPadding())/(float)atlas->height;

    FT_Load_Glyph( face, glyph_index,
                   FT_LOAD_RENDER | FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT);
    glyph->advance_x = (int)round(ratio * face->glyph->advance.x/64.0 * (1 + 2*getPadding()));
    glyph->advance_y = (int)round(ratio * face->glyph->advance.y/64.0 * (1 + 2*getPadding()));

    delete[] highres_data;
    delete[] lowres_data;
    delete[] data;

    vector_push_back( font_->glyphs, &glyph );
}




void FTFont::populateMeshDataForString(FTFontMeshData* data, const std::basic_string<wchar_t>& text, float point_size) {
    auto* atlas = font_texture_->getTextureAtlas();
    size_t length = text.length();
    auto& vertices = data->getVertices();
    auto& indices = data->getIndices();
    auto& glyph_starts = data->getGlyphStarts();

    glm::vec2 pen;
    int curIndex = 0;
    size_t i;

    FTVertexTexture<glm::vec2> vertex;

    // TODO: Rework to use UTF-8 everywhere
    std::vector<char> buffer(MB_CUR_MAX);

    bool texture_dirty = false;

    float maxHeight = 0.0f;

    float sf = point_size / font_->size;

    //float r = color->red, g = color->green, b = color->blue, a = color->alpha;
    for (i = 0; i < length; ++i) {
        wctomb(buffer.data(), text[i]);

        auto before = atlas->used;
        texture_glyph_t* glyph = texture_font_get_glyph(font_, buffer.data());
        // This is a hack to determine if the texture has been modified
        texture_dirty |= atlas->used != before;

        if (glyph != nullptr) {
            float kerning = 0.0f;
            if (i > 0) {
                wctomb(buffer.data(), text[i - 1]);
                kerning = texture_glyph_get_kerning(glyph, buffer.data());
            }
            pen.x += kerning;
            glyph_starts.push_back(pen.x);

            float x0 = pen.x + glyph->offset_x * sf;
            float y0 = pen.y + glyph->offset_y * sf;
            float x1 = x0 + glyph->width * sf;
            float y1 = y0 - glyph->height * sf;
            maxHeight = FTMAX(maxHeight, FTMAX(y0,y1));

            float s0 = glyph->s0;
            float t0 = glyph->t0;
            float s1 = glyph->s1;
            float t1 = glyph->t1;



            // NB Do not modify the vertex ordering without also adjusting
            // the FTFontMeshData::getGlyphBounds
            vertex.position_ = glm::vec2(x0, y0);
            vertex.uv_ = glm::vec2(s0, t0);
            vertices.push_back(vertex);

            vertex.position_ = glm::vec2(x1, y0);
            vertex.uv_ = glm::vec2(s1, t0);
            vertices.push_back(vertex);

            vertex.position_ = glm::vec2(x1, y1);
            vertex.uv_ = glm::vec2(s1, t1);
            vertices.push_back(vertex);

            vertex.position_ = glm::vec2(x0, y1);
            vertex.uv_ = glm::vec2(s0, t1);
            vertices.push_back(vertex);
            

            pen.x += glyph->advance_x * sf;

            indices.push_back(curIndex);
            indices.push_back(curIndex + 3);
            indices.push_back(curIndex + 1);
            indices.push_back(curIndex + 3);
            indices.push_back(curIndex + 2);
            indices.push_back(curIndex + 1);
            curIndex += 4;
        }
    }
    glyph_starts.push_back(pen.x);
    data->setBoundingShape(std::make_unique<FTBoundingCuboid>(glm::vec3(pen.x, maxHeight, 0)));
}
