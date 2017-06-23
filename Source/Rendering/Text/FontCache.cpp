#include "FontCache.h"
#include "Frontier.h"

NS_FT_BEGIN

FontCache::FontCache() {
    FTLOG("FontCache Init");
}

FontCache::~FontCache() {
    FTLOG("FontCache Destroyed");
}

void FontCache::loadFontStyle(const std::string &style, const std::string &filename, const glm::vec3& color) {
    if (loaded_styles.find(style) != loaded_styles.end())
        return;

    auto it = loaded_fonts_.find(filename);
    if (it == loaded_fonts_.end()) {
        auto font = std::make_unique<Font>(filename);
        font->updateTexture();
        loaded_fonts_[filename] = std::move(font);
        it = loaded_fonts_.find(filename);
    }

    Material material;
    material.texture = it->second->getTexture();
    material.diffuse_color = color;
    Engine::getDirector()->getMaterialCache()->loadMaterial(style, material);

    loaded_styles[style] = std::make_pair(it->second.get(), Engine::getDirector()->getMaterialCache()->getMaterial(style));
}

NS_FT_END