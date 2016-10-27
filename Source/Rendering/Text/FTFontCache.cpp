#include "FTFontCache.h"
#include "Frontier.h"

FTFontCache::FTFontCache() {
    FTLOG("FTFontCache Init");
}

FTFontCache::~FTFontCache() {
    FTLOG("FTFontCache Destroyed");
}

bool FTFontCache::loadFont(const std::string& filename) {
    if (loaded_fonts_.find(filename) != loaded_fonts_.end()) {
        return false;
    }
    (loaded_fonts_[filename] = std::make_shared<FTFont>(filename))->updateTexture();
    return true;
}
