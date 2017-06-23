#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/IndexedMesh.h>
#include <Rendering/Texture/FontTexture.h>
#include <unordered_map>
#include <freetype-gl.h>

namespace ftgl
{
    struct texture_font_t;
}

NS_FT_BEGIN

class FontMeshData : public IndexedMeshData<VertexTexture<glm::vec2>, uint16_t> {
private:
    typedef IndexedMeshData<VertexTexture<glm::vec2>, uint16_t> FTFontMeshDataBase_;
public:
    FontMeshData() {

    }

    FontMeshData(size_t vertexCount, size_t index_count) : FTFontMeshDataBase_(vertexCount, index_count) {
        
    }

    FontMeshData(std::vector<VertexTexture<glm::vec2>>&& vertices, std::vector<uint16_t>&& indices) : FTFontMeshDataBase_(std::move(vertices), std::move(indices)) {
    }

    std::pair<float, float> getGlyphBounds(size_t index) {
        FTAssert(index >= 0, "Invalid Glyph Index")
        FTAssert(index + 1 < glyph_starts_.size(), "Invalid Glyph Index");
        return std::make_pair(glyph_starts_[index], glyph_starts_[index+1]);
    }

    void clear() {
        vertices_.clear();
        indices_.clear();
        glyph_starts_.clear();
        index_count_ = 0;
        vertex_count_ = 0;
    }

    std::vector<float>& getGlyphStarts() {
        return glyph_starts_;
    }

protected:

    std::vector<float> glyph_starts_;
};

class Font {
public:
    explicit Font(const std::string& filename, const char* cache =
            " !\"#$%&'()*+,-./0123456789:;<=>?"
            "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
            "`abcdefghijklmnopqrstuvwxyz{|}~");
    virtual ~Font();

    std::shared_ptr<FontTexture>& getTexture() {
        return font_texture_;
    }

    ftgl::texture_font_t* getTextureFont() {
        return font_;
    }

    std::unique_ptr<FontMeshData> generateMeshForString(const std::basic_string<wchar_t>& string, float point_size);
    void populateMeshDataForString(FontMeshData* data, const std::basic_string<wchar_t>& string, float point_size);

    static constexpr float getPointSize() {
        return 48;
    }

    static constexpr float getLowResSize() {
        return 48*2;
    }

    static constexpr float getHighResSize() {
        return 512;
    }

    static constexpr float getPadding() {
        return 0.1f;
    }

    void updateTexture() {
        font_texture_->flushData();
    }


protected:
    std::shared_ptr<FontTexture> font_texture_;
    ftgl::texture_font_t* font_;

    void add_glyph(const char *codepoint);
};

NS_FT_END
