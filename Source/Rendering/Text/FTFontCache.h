#pragma once
#include <Frontier.h>
#include <Rendering/Text/FTFont.h>

class FTFontCache {
    friend class FTDirector;
public:

    void loadFontStyle(const std::string &style, const std::string& fontpath);

    std::pair<FTFont*, FTMaterial*> getFontStyle(const std::string& style) {
        auto it = loaded_styles.find(style);
        FTAssert(it != loaded_styles.end(), "Could not find Font Style %s", style.c_str());
        return it->second;
    }

protected:
    std::unordered_map<std::string, std::unique_ptr<FTFont>> loaded_fonts_;
    std::unordered_map<std::string, std::pair<FTFont*, FTMaterial*>> loaded_styles;

    FTFontCache();
    ~FTFontCache();
};
