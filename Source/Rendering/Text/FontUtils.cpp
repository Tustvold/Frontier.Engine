#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <IO/Serialization/Serialization.h>
#include "FontUtils.h"

NS_FT_BEGIN

template<typename Archiver>
struct Serializer<Archiver, ftgl::texture_glyph_t *> {
    static void serialize(Archiver &a, ftgl::texture_glyph_t *&val) {
        if (Archiver::is_input) {
            val = (texture_glyph_t *) malloc(sizeof(texture_glyph_t));
        }

        uint8_t t = (uint8_t) val->rendermode;
        a & t;
        if (Archiver::is_input)
            val->rendermode = (rendermode_t) t;

        a & val->width;
        a & val->height;
        a & val->outline_thickness;
        a & val->kerning;
        a & val->advance_x;
        a & val->advance_y;
        a & val->codepoint;
        a & val->offset_x;
        a & val->offset_y;
        a & val->s0;
        a & val->s1;
        a & val->t0;
        a & val->t1;
    }
};


template<typename Archiver>
struct Serializer<Archiver, ftgl::vector_t *> {
    static void serialize(Archiver &a, ftgl::vector_t *&val) {
        if (Archiver::is_input) {
            val = (vector_t *) malloc(sizeof(vector_t));
        }

        a & val->size;
        a & val->item_size;

        if (Archiver::is_input) {
            val->capacity = val->size;
            val->items = malloc(val->size * val->item_size);
        }

        a.serializePrimitiveArray((uint8_t *) val->items, val->size * val->item_size);
    }
};

template<typename Archiver>
struct Serializer<Archiver, ftgl::texture_atlas_t *> {
    static void serialize(Archiver &a, ftgl::texture_atlas_t *&val) {
        if (Archiver::is_input) {
            val = (ftgl::texture_atlas_t *) malloc(sizeof(ftgl::texture_atlas_t));
        }
        a & val->depth;
        a & val->width;
        a & val->height;
        a & val->id;
        a & val->nodes;
        a & val->used;

        if (Archiver::is_input) {
            val->data = (unsigned char *) malloc(val->width * val->height * val->depth * sizeof(unsigned char));
        }

        a.serializePrimitiveArray(val->data, val->width * val->height * val->depth);
    }
};

template<typename Archiver>
struct Serializer<Archiver, ftgl::texture_font_t *> {
    static void serialize(Archiver &a, ftgl::texture_font_t *&val) {
        if (Archiver::is_input) {
            val = (ftgl::texture_font_t *) malloc(sizeof(ftgl::texture_font_t));
            val->filename = strdup("");
        }
        a & val->size;

        if (Archiver::is_input) {
            size_t size;
            a & size;
            val->glyphs = vector_new(sizeof(texture_glyph_t *));
            vector_resize(val->glyphs, size);
        } else {
            a & val->glyphs->size;
        }

        for (size_t i = 0; i < vector_size(val->glyphs); ++i) {
            a & *(texture_glyph_t **) vector_get(val->glyphs, i);
        }

        a & val->ascender;
        a & val->atlas;
        a & val->descender;
        a & val->filtering;
        a & val->height;
        a & val->hinting;
        a & val->kerning;
        a & val->lcd_weights;
        a & val->linegap;
        a & val->outline_thickness;

        uint8_t t = (uint8_t) val->rendermode;
        a & t;
        if (Archiver::is_input)
            val->rendermode = (rendermode_t) t;

        a & val->underline_position;
        a & val->underline_thickness;
    }
};

void FontUtils::serializeFont(ftgl::texture_font_t *font, ttvfs::File *file) {
    OutputSerializer out(file);
    out & font;
}

ftgl::texture_font_t *FontUtils::deserializeFont(ttvfs::File *file) {
    ftgl::texture_font_t *ret;
    InputSerializer in(file);
    in & ret;
    return ret;
}

NS_FT_END
