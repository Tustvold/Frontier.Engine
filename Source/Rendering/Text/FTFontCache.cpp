#include "FTFontCache.h"
#include "Frontier.h"

FTFontCache* FTFontCache::getSharedInstance() {
    static FTFontCache* instance = new FTFontCache();
    return instance;
}

FTFontCache::FTFontCache() {
    FTLOG("FTFontCache Init");
}

FTFontCache::~FTFontCache() {
    FTLOG("FTFontCache Destroyed");
}

bool FTFontCache::loadFont(const std::basic_string<char>& filename) {
    if (loaded_fonts_.find(filename) != loaded_fonts_.end()) {
        return false;
    }
    loaded_fonts_[filename] = std::make_shared<FTFont>(filename);
    return true;
}
