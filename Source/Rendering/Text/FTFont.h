#pragma once
#include <FTObject.h>
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>
#include <Rendering/Textures/FTFontTexture.h>
#include <FTString.h>
#include <unordered_map>

struct texture_font_t;

class FTFont : public FTObject {
public:
	explicit FTFont(FTString<char>* filename);
	virtual ~FTFont();

	FTTexture* getTexture() {
		return font_texture_;
	}

	texture_font_t* cacheFontSize(int size);

	FTIndexedMeshData<FTVertexColorTexture, uint16_t>* generateMeshForString(const wchar_t* string, int size, glm::vec2& outputsize);

	void populateMeshDataForString(FTIndexedMeshData<FTVertexColorTexture, uint16_t>* data, const wchar_t* string, int size, glm::vec2& outputsize);

protected:
	float h;
	GLuint *textures;
	GLuint list_base;

	FTFontTexture* font_texture_;
	FTString<char>* font_name_;
	std::unordered_map<int, texture_font_t*> fonts_;
};