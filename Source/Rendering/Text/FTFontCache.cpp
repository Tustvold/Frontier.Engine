#include "FTFontCache.h"
#include "Frontier.h"

FTFontCache::FTFontCache() {
    FTLOG("FTFontCache Init");
}

FTFontCache::~FTFontCache() {
    FTLOG("FTFontCache Destroyed");
}

void FTFontCache::loadFontStyle(const std::string &style, const std::string &filename) {
    if (loaded_styles.find(style) != loaded_styles.end())
        return;

    auto it = loaded_fonts_.find(filename);
    if (it == loaded_fonts_.end()) {
        auto font = std::make_unique<FTFont>(filename);
        font->updateTexture();
        loaded_fonts_[filename] = std::move(font);
        it = loaded_fonts_.find(filename);
    }

    FTMaterial material;
    material.texture = it->second->getTexture();
    FTEngine::getDirector()->getMaterialCache()->loadMaterial(style, material);

    loaded_styles[style] = std::make_pair(it->second.get(), FTEngine::getDirector()->getMaterialCache()->getMaterial(style));
}