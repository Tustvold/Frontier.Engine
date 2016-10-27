#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include "FTFontUtils.h"

enum class FTFontTag {
    Data,
    Depth,
    Height,
    Width,
    Nodes,
    Used,
    VectorData,
    VectorSize,
    VectorItemSize,
    Glyphs,
    Atlas,
    Size,
    Hinting,
    RenderMode,
    OutlineThickness,
    Filtering,
    LCDWeights,
    Kerning,
    LineGap,
    Ascender,
    Descender,
    UnderlinePosition,
    UnderlineThickness,
    Codepoint,
    OffsetX,
    OffsetY,
    AdvanceX,
    AdvanceY,
    S0,
    S1,
    T0,
    T1
};


std::unique_ptr<Tag> FTFontUtils::createTagForVector(const vector_t *v) {
    auto root = std::make_unique<Tag>(Tag::TAG_Compound);

    auto data = std::make_unique<Tag>(Tag::TAG_Byte_Array);
    uint8_t* bytes = (uint8_t*)v->items;
    data->payload_byteArray->data.reserve(v->size * v->item_size);
    std::copy(bytes, bytes + v->size * v->item_size, std::back_inserter(data->payload_byteArray->data));
    root->payload_tagCompound->addTag(std::move(data), (uint16_t)FTFontTag::VectorData);

    auto size = std::make_unique<Tag>(Tag::TAG_UInt32);
    size->payload_uint = (uint32_t) v->size;
    root->payload_tagCompound->addTag(std::move(size), (uint16_t)FTFontTag::VectorSize);

    auto item_size = std::make_unique<Tag>(Tag::TAG_UInt32);
    item_size->payload_uint = (uint32_t) v->item_size;
    root->payload_tagCompound->addTag(std::move(item_size), (uint16_t)FTFontTag::VectorItemSize);

    return root;
}

vector_t* FTFontUtils::createVectorFromTag(Tag* tag) {
    FTAssert(tag->type == Tag::TAG_Compound, "Invalid Tag");

    auto item_size = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::VectorItemSize, Tag::TAG_UInt32)->payload_uint;
    auto size = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::VectorSize, Tag::TAG_UInt32)->payload_uint;


    auto data = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::VectorData, Tag::TAG_Byte_Array);
    vector_t* v = vector_new(item_size);
    vector_resize(v, size);
    std::copy(data->payload_byteArray->data.begin(), data->payload_byteArray->data.end(), (uint8_t*)v->items);

    return v;
}

std::unique_ptr<Tag> FTFontUtils::createTagForAtlas(const ftgl::texture_atlas_t *texture_atlas) {
    auto root = std::make_unique<Tag>(Tag::TAG_Compound);

    auto depth = std::make_unique<Tag>(Tag::TAG_UInt32);
    depth->payload_uint = (uint32_t)texture_atlas->depth;
    root->payload_tagCompound->addTag(std::move(depth), (uint16_t)FTFontTag::Depth);

    auto height = std::make_unique<Tag>(Tag::TAG_UInt32);
    height->payload_uint = (uint32_t)texture_atlas->height;
    root->payload_tagCompound->addTag(std::move(height), (uint16_t)FTFontTag::Height);


    auto width = std::make_unique<Tag>(Tag::TAG_UInt32);
    width->payload_uint = (uint32_t)texture_atlas->width;
    root->payload_tagCompound->addTag(std::move(width), (uint16_t)FTFontTag::Width);

    auto used = std::make_unique<Tag>(Tag::TAG_UInt32);
    used->payload_uint = (uint32_t)texture_atlas->used;
    root->payload_tagCompound->addTag(std::move(used), (uint16_t)FTFontTag::Used);

    root->payload_tagCompound->addTag(createTagForVector(texture_atlas->nodes), (uint16_t)FTFontTag::Nodes);

    auto data = std::make_unique<Tag>(Tag::TAG_Byte_Array);
    uint8_t* bytes = texture_atlas->data;
    data->payload_byteArray->data.reserve(texture_atlas->width * texture_atlas->height);
    std::copy(bytes, bytes + texture_atlas->width * texture_atlas->height * texture_atlas->depth, std::back_inserter(data->payload_byteArray->data));
    root->payload_tagCompound->addTag(std::move(data), (uint16_t)FTFontTag::Data);

    return root;
}

ftgl::texture_atlas_t* FTFontUtils::createAtlasForTag(Tag* tag) {
    FTAssert(tag->type == Tag::TAG_Compound, "Invalid Tag");
    texture_atlas_t* atlas = (texture_atlas_t *) malloc( sizeof(texture_atlas_t));
    atlas->depth = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Depth, Tag::TAG_UInt32)->payload_uint;
    atlas->height = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Height, Tag::TAG_UInt32)->payload_uint;
    atlas->width = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Width, Tag::TAG_UInt32)->payload_uint;
    atlas->used = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Used, Tag::TAG_UInt32)->payload_uint;

    atlas->nodes = createVectorFromTag(tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Nodes, Tag::TAG_Compound));
    atlas->data = (unsigned char *) malloc( atlas->width*atlas->height*atlas->depth * sizeof(unsigned char) );

    auto data = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Data, Tag::TAG_Byte_Array);
    FTAssert(data->payload_byteArray->data.size() == atlas->width*atlas->height*atlas->depth, "Invalid Data");
    std::copy(data->payload_byteArray->data.begin(), data->payload_byteArray->data.end(), atlas->data);
    return atlas;
}

std::unique_ptr<Tag> FTFontUtils::createTagForFont(ftgl::texture_font_t* font) {
    auto root = std::make_unique<Tag>(Tag::TAG_Compound);


    auto glyphs = std::make_unique<Tag>(Tag::TAG_List);
    for(int i=0; i<vector_size(font->glyphs); ++i ) {
        texture_glyph_t * glyph = *(texture_glyph_t **) vector_get(font->glyphs, i );
        glyphs->payload_tagList->addTag(createTagForGlyph(glyph));
    }
    root->payload_tagCompound->addTag(std::move(glyphs), (uint16_t)FTFontTag::Glyphs);

    auto atlas = createTagForAtlas(font->atlas);
    root->payload_tagCompound->addTag(std::move(atlas), (uint16_t)FTFontTag::Atlas);

    auto tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = font->size;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::Size);

    tag = std::make_unique<Tag>(Tag::TAG_Int32);
    tag->payload_int = font->hinting;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::Hinting);

    tag = std::make_unique<Tag>(Tag::TAG_Int32);
    tag->payload_int = font->rendermode;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::RenderMode);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = font->outline_thickness;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::OutlineThickness);

    tag = std::make_unique<Tag>(Tag::TAG_Int32);
    tag->payload_int = font->filtering;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::Filtering);

    tag = std::make_unique<Tag>(Tag::TAG_Byte_Array);
    std::copy(font->lcd_weights, font->lcd_weights + 5, std::back_inserter(tag->payload_byteArray->data));
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::LCDWeights);

    tag = std::make_unique<Tag>(Tag::TAG_Int32);
    tag->payload_int = font->kerning;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::Kerning);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = font->height;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::Height);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = font->linegap;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::LineGap);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = font->ascender;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::Ascender);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = font->descender;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::Descender);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = font->underline_position;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::UnderlinePosition);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = font->underline_thickness;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::UnderlineThickness);

    return root;
}

ftgl::texture_font_t* FTFontUtils::createFontForTag(Tag* tag) {
    FTAssert(tag->type == Tag::TAG_Compound, "Invalid Tag");

    ftgl::texture_font_t* font = (ftgl::texture_font_t*)malloc(sizeof(ftgl::texture_font_t));
    font->glyphs = vector_new(sizeof(texture_glyph_t*));
    auto glyphs_tag = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Glyphs, Tag::TAG_List);
    for (const auto& it : glyphs_tag->payload_tagList->data) {
        auto glyph = createGlyphForTag(it.get());
        vector_push_back(font->glyphs, &glyph);
    }

    font->atlas = createAtlasForTag(tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Atlas, Tag::TAG_Compound));

    font->ascender = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Ascender, Tag::TAG_Float)->payload_float;
    font->descender = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Descender, Tag::TAG_Float)->payload_float;
    font->filename = strdup("");
    font->filtering = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Filtering, Tag::TAG_Int32)->payload_int;
    font->height = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Height, Tag::TAG_Float)->payload_float;
    font->hinting = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Hinting, Tag::TAG_Int32)->payload_int;
    font->kerning = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Kerning, Tag::TAG_Int32)->payload_int;
    font->hinting = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Hinting, Tag::TAG_Int32)->payload_int;
    font->linegap = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::LineGap, Tag::TAG_Float)->payload_float;
    font->outline_thickness = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::OutlineThickness, Tag::TAG_Float)->payload_float;
    font->rendermode = (rendermode_t)tag->payload_tagCompound->getTag((uint16_t)FTFontTag::RenderMode, Tag::TAG_Int32)->payload_int;
    font->size = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Size, Tag::TAG_Float)->payload_float;
    font->underline_position = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::UnderlinePosition, Tag::TAG_Float)->payload_float;
    font->underline_thickness = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::UnderlineThickness, Tag::TAG_Float)->payload_float;

    auto lcd_weights = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::LCDWeights, Tag::TAG_Byte_Array)->payload_byteArray;
    for (int i = 0; i < 5; i++)
        font->lcd_weights[i] = lcd_weights->data[i];

    font->location = texture_font_t::TEXTURE_FONT_FILE;

    return font;
}

std::unique_ptr<Tag> FTFontUtils::createTagForGlyph(ftgl::texture_glyph_t* glyph) {
    auto root = std::make_unique<Tag>(Tag::TAG_Compound);
    root->payload_tagCompound->addTag(FTFontUtils::createTagForVector(glyph->kerning), (uint16_t)FTFontTag::Kerning);


    auto tag = std::make_unique<Tag>(Tag::TAG_UInt32);
    tag->payload_uint = glyph->codepoint;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::Codepoint);

    tag = std::make_unique<Tag>(Tag::TAG_UInt32);
    tag->payload_uint = (uint32_t)glyph->width;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::Width);

    tag = std::make_unique<Tag>(Tag::TAG_UInt32);
    tag->payload_uint = (uint32_t)glyph->height;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::Height);

    tag = std::make_unique<Tag>(Tag::TAG_Int32);
    tag->payload_int = glyph->offset_x;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::OffsetX);

    tag = std::make_unique<Tag>(Tag::TAG_Int32);
    tag->payload_int = glyph->offset_y;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::OffsetY);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = glyph->advance_x;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::AdvanceX);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = glyph->advance_y;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::AdvanceY);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = glyph->s0;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::S0);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = glyph->s1;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::S1);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = glyph->t0;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::T0);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = glyph->t1;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::T1);

    tag = std::make_unique<Tag>(Tag::TAG_UInt32);
    tag->payload_uint = glyph->rendermode;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::RenderMode);

    tag = std::make_unique<Tag>(Tag::TAG_Float);
    tag->payload_float = glyph->outline_thickness;
    root->payload_tagCompound->addTag(std::move(tag), (uint16_t)FTFontTag::OutlineThickness);

    return root;
}

ftgl::texture_glyph_t* FTFontUtils::createGlyphForTag(Tag* tag) {
    texture_glyph_t* ret = (texture_glyph_t*)malloc(sizeof(texture_glyph_t));
    ret->codepoint = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Codepoint, Tag::TAG_UInt32)->payload_uint;
    ret->width = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Width, Tag::TAG_UInt32)->payload_uint;
    ret->height = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Height, Tag::TAG_UInt32)->payload_uint;
    ret->offset_x = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::OffsetX, Tag::TAG_Int32)->payload_int;
    ret->offset_y = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::OffsetY, Tag::TAG_Int32)->payload_int;
    ret->advance_x = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::AdvanceX, Tag::TAG_Float)->payload_float;
    ret->advance_y = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::AdvanceY, Tag::TAG_Float)->payload_float;

    ret->s0 = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::S0, Tag::TAG_Float)->payload_float;
    ret->s1 = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::S1, Tag::TAG_Float)->payload_float;
    ret->t0 = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::T0, Tag::TAG_Float)->payload_float;
    ret->t1 = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::T1, Tag::TAG_Float)->payload_float;

    ret->kerning = FTFontUtils::createVectorFromTag(tag->payload_tagCompound->getTag((uint16_t)FTFontTag::Kerning, Tag::TAG_Compound));
    ret->rendermode = (rendermode_t)tag->payload_tagCompound->getTag((uint16_t)FTFontTag::RenderMode, Tag::TAG_UInt32)->payload_uint;
    ret->outline_thickness = tag->payload_tagCompound->getTag((uint16_t)FTFontTag::OutlineThickness, Tag::TAG_Float)->payload_float;
    return ret;
}