#pragma once
#include <Frontier.h>
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>
#include <Rendering/Textures/FTFontTexture.h>
#include <unordered_map>

namespace ftgl
{
    struct texture_font_t;
}

struct texture_font_t;

class FTFontMeshData : public FTIndexedMeshData<FTVertexTexture<glm::vec2>, uint16_t> {
private:
    typedef FTIndexedMeshData<FTVertexTexture<glm::vec2>, uint16_t> FTFontMeshDataBase_;
public:
    FTFontMeshData() {

    }

    FTFontMeshData(size_t vertexCount, size_t index_count) : FTFontMeshDataBase_(vertexCount, index_count) {
        
    }

    FTFontMeshData(std::vector<FTVertexTexture<glm::vec2>>&& vertices, std::vector<uint16_t>&& indices) : FTFontMeshDataBase_(std::move(vertices), std::move(indices)) {
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

class FTFont {
public:
    explicit FTFont(const std::string& filename);
    virtual ~FTFont();

    std::shared_ptr<FTFontTexture>& getTexture() {
        return font_texture_;
    }

    ftgl::texture_font_t* cacheFontSize(int size);

    std::unique_ptr<FTFontMeshData> generateMeshForString(const std::basic_string<wchar_t>& string, int size);

    void populateMeshDataForString(FTFontMeshData* data, const std::basic_string<wchar_t>& string, int size);

protected:
    std::shared_ptr<FTFontTexture> font_texture_;
    std::string font_path_;
    std::unordered_map<int, ftgl::texture_font_t*> fonts_;
};
