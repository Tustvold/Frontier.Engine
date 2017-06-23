#pragma once
#include <Frontier.h>
#include <Rendering/Text/Font.h>

NS_FT_BEGIN

class FontCache {
    friend class Director;
public:

    void loadFontStyle(const std::string &style, const std::string& fontpath, const glm::vec3& color = glm::vec3(0,0,0));

    std::pair<Font*, Material*> getFontStyle(const std::string& style) {
        auto it = loaded_styles.find(style);
        FTAssert(it != loaded_styles.end(), "Could not find Font Style %s", style.c_str());
        return it->second;
    }

protected:
    std::unordered_map<std::string, std::unique_ptr<Font>> loaded_fonts_;
    std::unordered_map<std::string, std::pair<Font*, Material*>> loaded_styles;

    FontCache();
    ~FontCache();
};

NS_FT_END