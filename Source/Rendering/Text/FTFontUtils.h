#pragma once

#include <Util/Serialization/Serialization.h>
#include "Frontier.h"
#include "freetype-gl.h"

class FTFontUtils {
public:
    static void serializeFont(ftgl::texture_font_t *font, ttvfs::File *file);

    static ftgl::texture_font_t* deserializeFont(ttvfs::File *file);
};




