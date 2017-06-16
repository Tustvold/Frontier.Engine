#include <Util/BTF/Tag.h>
#include <gtest/gtest.h>
#include <stdlib.h>
#include <malloc.h>
#include "Rendering/Text/FTFontUtils.h"
#include "Rendering/Text/FTFont.h"
#include "Mock/MockLoader.h"
#include <FTEngine.h>
#include<Util/FTFileManager.h>

void expectVectorEqual(vector_t*a, vector_t*b) {
    EXPECT_EQ(a->size, b->size);
    EXPECT_EQ(a->item_size, b->item_size);

    for (size_t i = 0; i < b->size * b->item_size; i++) {
        EXPECT_EQ(((uint8_t*)a->items)[i], ((uint8_t*)b->items)[i]);
    }
}

void expectAtlasEqual(texture_atlas_t* a, texture_atlas_t* b) {
    EXPECT_EQ(a->depth, b->depth);
    EXPECT_EQ(a->height, b->height);
    EXPECT_EQ(a->width, b->width);
    EXPECT_EQ(a->depth, b->depth);
    EXPECT_EQ(a->used, b->used);

    expectVectorEqual(a->nodes, b->nodes);

    for (size_t i = 0; i < a->depth* a->width * a->height; i++)
        EXPECT_EQ(a->data[i], b->data[i]);
}

void expectGlyphEqual(texture_glyph_t* a, texture_glyph_t* b) {
    expectVectorEqual(a->kerning, b->kerning);
    EXPECT_EQ(a->codepoint,b->codepoint);
    EXPECT_EQ(a->width,b->width);
    EXPECT_EQ(a->height,b->height);
    EXPECT_EQ(a->offset_x,b->offset_x);
    EXPECT_EQ(a->offset_y,b->offset_y);
    EXPECT_EQ(a->advance_x,b->advance_x);
    EXPECT_EQ(a->advance_y,b->advance_y);
    EXPECT_EQ(a->s0,b->s0);
    EXPECT_EQ(a->t0,b->t0);
    EXPECT_EQ(a->s1,b->s1);
    EXPECT_EQ(a->t1,b->t1);
    EXPECT_EQ(a->rendermode,b->rendermode);
    EXPECT_EQ(a->outline_thickness,b->outline_thickness);
}

TEST(TestFontUtils, VectorTest) {
    MockLoader mock;
    auto font = std::make_shared<FTFont>("TestResources/Fonts/Vera.ttf", "@!");
    auto texture_font = font->getTextureFont();

    auto out_tag = FTFontUtils::createTagForVector(texture_font->glyphs);
    auto in_vector = FTFontUtils::createVectorFromTag(out_tag.get());

    expectVectorEqual(in_vector, texture_font->glyphs);

    vector_delete(in_vector);
}

TEST(TestFontUtils, AtlasTest) {
    MockLoader mock;
    auto font = std::make_shared<FTFont>("TestResources/Fonts/Vera.ttf", "@!");
    auto texture_font = font->getTextureFont();

    auto out_atlas = texture_font->atlas;
    auto out_tag = FTFontUtils::createTagForAtlas(out_atlas);
    auto in_atlas = FTFontUtils::createAtlasForTag(out_tag.get());
    expectAtlasEqual(out_atlas, in_atlas);

    texture_atlas_delete(in_atlas);
}

TEST(TestFontUtils, FontTest) {
    MockLoader mock;
    auto font = std::make_shared<FTFont>("TestResources/Fonts/Vera.ttf", "@!");
    auto out_font = font->getTextureFont();

    auto out_tag = FTFontUtils::createTagForFont(out_font);
    auto in_font = FTFontUtils::createFontForTag(out_tag.get());

    expectAtlasEqual(out_font->atlas, in_font->atlas);
    EXPECT_EQ(vector_size(in_font->glyphs), vector_size(out_font->glyphs));
    for(size_t i=0; i<vector_size(in_font->glyphs); ++i ) {
        texture_glyph_t * a = *(texture_glyph_t **) vector_get(in_font->glyphs, i );
        texture_glyph_t * b = *(texture_glyph_t **) vector_get(out_font->glyphs, i );
        expectGlyphEqual(a,b);
    }

    EXPECT_EQ(out_font->underline_position, in_font->underline_position);
    EXPECT_EQ(out_font->underline_thickness, in_font->underline_thickness);
    EXPECT_EQ(out_font->size, in_font->size);
    EXPECT_EQ(out_font->ascender, in_font->ascender);
    EXPECT_EQ(out_font->descender, in_font->descender);
    EXPECT_EQ(out_font->filtering, in_font->filtering);
    EXPECT_EQ(out_font->height, in_font->height);
    EXPECT_EQ(out_font->hinting, in_font->hinting);
    EXPECT_EQ(out_font->linegap, in_font->linegap);
    EXPECT_EQ(out_font->rendermode, in_font->rendermode);
    EXPECT_EQ(out_font->outline_thickness, in_font->outline_thickness);
    EXPECT_EQ(out_font->kerning, in_font->kerning);
    for (int i = 0; i < 5; i++)
        EXPECT_EQ(out_font->lcd_weights[i], in_font->lcd_weights[i]);
}

TEST(TestFontUtils, GlyphTest) {
    MockLoader mock;
    auto font = std::make_shared<FTFont>("TestResources/Fonts/Vera.ttf", "@!");
    auto out_font = font->getTextureFont();

    auto glyph = texture_font_get_glyph(out_font, "@");
    auto out_tag = FTFontUtils::createTagForGlyph(glyph);
    auto in_glyph = FTFontUtils::createGlyphForTag(out_tag.get());

    expectGlyphEqual(glyph, in_glyph);

    vector_delete(in_glyph->kerning);
    free(in_glyph);
}

TEST(TestFontUtils, FTFontFile) {
    MockLoader mock;
    auto font = std::make_shared<FTFont>("TestResources/Fonts/Vera.ttf");
    auto write = FTFontUtils::createTagForFont(font->getTextureFont());

    auto buffer = std::make_unique<CompressionBuffer>();
    write->writeToBuffer(buffer.get());

    ttvfs::File *file = FTEngine::getFileManager()->getOrCreateFile("TestResources/Vera.ftfont");
    file->open("wb");
    buffer->writeFile(file);
    file->close();

    auto font_test = std::make_shared<FTFont>("TestResources/Vera.ftfont");
    font_test.reset();
}