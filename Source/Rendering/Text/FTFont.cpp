#include "FTFont.h"
#include "freetype-gl.h"
#include <Rendering/Mesh/FTIndexedTexturedMesh.h>

FTFont::FTFont(FTString<char> *filename) : font_name_(filename) {
	//font_name_->retain();
	font_name_->retain();
	texture_atlas_t* texture_atlas = texture_atlas_new(512, 512, 1);
	font_texture_ = new FTFontTexture(texture_atlas);
	
	//FTLOG("Loaded font                : %s", filename);
	//FTLOG("Texture occupancy          : %.2f%%", 100.0*texture_atlas->used / (float)(texture_atlas->width*texture_atlas->height));
}

FTFont::~FTFont() {
	for (auto it = fonts_.begin(); it != fonts_.end(); ++it) {
		texture_font_delete(it->second);
	}

	font_name_->release();
	font_texture_->release();
}

texture_font_t* FTFont::cacheFontSize(int size) {
	static const wchar_t *cache = L" !\"#$%&'()*+,-./0123456789:;<=>?"
		L"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
		L"`abcdefghijklmnopqrstuvwxyz{|}~";

	auto it = fonts_.find(size);
	if (it != fonts_.end())
		return it->second;

	texture_font_t* font = texture_font_new_from_file(font_texture_->getTextureAtlas(), (float)(size), font_name_->getCString());
	size_t missed = texture_font_load_glyphs(font, cache);
	fonts_[size] = font;

	if (missed != 0)
		FTLogWarn("Font missing glyphs!");
	return font;
}

FTIndexedMeshData<FTVertexColorTexture, uint16_t>* FTFont::generateMeshForString(const wchar_t* text, int size, glm::vec2& pen) {
	texture_font_t* font = cacheFontSize(size);
	size_t length = wcslen(text);
	auto data = new FTIndexedMeshData<FTVertexColorTexture, uint16_t>(4 * length, 6 * length);
	auto vertices = data->getVertices();
	auto indices = data->getIndices();

	//glm::vec2 pen = glm::vec2();
	int curIndex = 0;
	size_t i;

	FTVertexColorTexture vertex;
	vertex.color_ = glm::vec3(0.5f, 0.5f, 0.5f);
	//float r = color->red, g = color->green, b = color->blue, a = color->alpha;
	for (i = 0; i < length; ++i)
	{
		texture_glyph_t *glyph = texture_font_get_glyph(font, text[i]);
		if (glyph != nullptr)
		{
			float kerning = 0.0f;
			if (i > 0)
			{
				kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
			}
			pen.x += kerning;


			int x0 = (int)(pen.x + glyph->offset_x);
			int y0 = (int)(pen.y + glyph->offset_y);
			int x1 = (int)(x0 + glyph->width);
			int y1 = (int)(y0 - glyph->height);

			float s0 = glyph->s0;
			float t0 = glyph->t0;
			float s1 = glyph->s1;
			float t1 = glyph->t1;

			vertex.position_ = glm::vec3(x0, y0, 0);
			vertex.uv_ = glm::vec2(s0, t0);
			vertices->add(vertex);

			vertex.position_ = glm::vec3(x1, y0, 0);
			vertex.uv_ = glm::vec2(s1, t0);
			vertices->add(vertex);

			vertex.position_ = glm::vec3(x0, y1, 0);
			vertex.uv_ = glm::vec2(s0, t1);
			vertices->add(vertex);

			vertex.position_ = glm::vec3(x1, y1, 0);
			vertex.uv_ = glm::vec2(s1, t1);
			vertices->add(vertex);

			pen.x += glyph->advance_x;

			indices->add(curIndex);
			indices->add(curIndex + 2);
			indices->add(curIndex + 1);
			indices->add(curIndex + 2);
			indices->add(curIndex + 3);
			indices->add(curIndex + 1);
			curIndex += 4;
		}
	}
	return data;
}