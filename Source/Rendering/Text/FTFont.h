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

    std::pair<glm::vec2, glm::vec2> getGlyphBounds(int index) {
        FTAssert(index >= 0, "Invalid Glyph Index")
        FTAssert(index * 4 + 2 < vertices_.size(), "Invalid Glyph Index");
        return std::make_pair(vertices_[index * 4].position_, vertices_[index*4 + 2].position_);
    }
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
