#include "freetype-gl.h"
#include "FTFont.h"
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>
#include <Util/FTFileManager.h>

FTFont::FTFont(const std::string& filename) : font_texture_(new FTFontTexture(texture_atlas_new(512, 512, 1))) {
    font_path_ = FTEngine::getFileManager()->getPathToFile(filename);
    FTAssert(font_path_ != "", "Failed to find font: %s", filename.c_str());
}

FTFont::~FTFont() {
    for (auto it = fonts_.begin(); it != fonts_.end(); ++it) {
        texture_font_delete(it->second);
    }
}

ftgl::texture_font_t* FTFont::cacheFontSize(int size) {
    static auto cache = " !\"#$%&'()*+,-./0123456789:;<=>?"
        "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
        "`abcdefghijklmnopqrstuvwxyz{|}~";

    auto it = fonts_.find(size);
    if (it != fonts_.end())
        return it->second;

    ftgl::texture_font_t* font = texture_font_new_from_file(font_texture_->getTextureAtlas(), (float)(size), font_path_.c_str());
    size_t missed = texture_font_load_glyphs(font, cache);
    font_texture_->flushData();

    fonts_[size] = font;

    if (missed != 0)
        FTLogWarn("Font missing glyphs!");
    return font;
}

std::unique_ptr<FTFontMeshData> FTFont::generateMeshForString(const std::basic_string<wchar_t>& text, int size) {
    size_t length = text.length();
    auto data = new FTFontMeshData(4 * length, 6 * length);
    populateMeshDataForString(data, text, size);
    return std::unique_ptr<FTFontMeshData>(data);
}

void FTFont::populateMeshDataForString(FTFontMeshData* data, const std::basic_string<wchar_t>& text, int size) {
    ftgl::texture_font_t* font = cacheFontSize(size);
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
    //float r = color->red, g = color->green, b = color->blue, a = color->alpha;
    for (i = 0; i < length; ++i) {
        wctomb(buffer.data(), text[i]);

        auto before = atlas->used;
        texture_glyph_t* glyph = texture_font_get_glyph(font, buffer.data());
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

            int x0 = (int)(pen.x + glyph->offset_x);
            int y0 = (int)(pen.y + glyph->offset_y);
            int x1 = (int)(x0 + glyph->width);
            int y1 = (int)(y0 - glyph->height);
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

            

            pen.x += glyph->advance_x;

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
