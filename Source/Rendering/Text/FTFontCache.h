#pragma once
#include <Frontier.h>
#include <Rendering/Text/FTFont.h>

NS_FT_BEGIN

class FTFontCache {
    friend class FTDirector;
public:

    void loadFontStyle(const std::string &style, const std::string& fontpath, const glm::vec3& color = glm::vec3(0,0,0));

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

NS_FT_END