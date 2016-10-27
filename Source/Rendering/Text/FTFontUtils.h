#pragma once
#include "Frontier.h"
#include "freetype-gl.h"
#include "Util/BTF/Tag.h"

class FTFontUtils {
public:
    static std::unique_ptr<Tag> createTagForVector(const vector_t* v);

    static std::unique_ptr<Tag> createTagForAtlas(const texture_atlas_t *texture_atlas);

    static vector_t *createVectorFromTag(Tag *tag);

    static texture_atlas_t *createAtlasForTag(Tag *tag);

    static std::unique_ptr<Tag> createTagForFont(ftgl::texture_font_t *font);

    static ftgl::texture_font_t *createFontForTag(Tag *tag);

    static std::unique_ptr<Tag> createTagForGlyph(texture_glyph_t *glyph);

    static texture_glyph_t *createGlyphForTag(Tag* glyph);
};


