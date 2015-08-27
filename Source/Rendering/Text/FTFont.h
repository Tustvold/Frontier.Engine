#pragma once
#include <FTObject.h>
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>
#include <Rendering/Textures/FTFontTexture.h>
#include <FTString.h>
#include <unordered_map>

struct texture_font_t;

class FTFont : public FTObject {
public:
	explicit FTFont(const std::basic_string<char>& filename);
	virtual ~FTFont();

	std::shared_ptr<FTFontTexture>& getTexture() {
		return font_texture_;
	}

	texture_font_t* cacheFontSize(int size);

	std::shared_ptr<FTIndexedMeshData<FTVertexColorTexture, uint16_t>> generateMeshForString(const std::basic_string<wchar_t>& string, int size, glm::vec2& outputsize);

	void populateMeshDataForString(std::shared_ptr<FTIndexedMeshData<FTVertexColorTexture, uint16_t>>& data, const std::basic_string<wchar_t>& string, int size, glm::vec2& outputsize);

protected:
	float h;
	GLuint* textures;
	GLuint list_base;

	std::shared_ptr<FTFontTexture> font_texture_;
	std::basic_string<char> font_name_;
	std::unordered_map<int, texture_font_t*> fonts_;
};
