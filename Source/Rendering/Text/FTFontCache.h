#pragma once
#include <Frontier.h>
#include <Rendering/Text/FTFont.h>

class FTFontCache {
    friend class FTDirector;
public:

    bool loadFont(const std::string& name);

    std::shared_ptr<FTFont>& getFont(const std::string& string) {
        auto it = loaded_fonts_.find(string);
        if (it == loaded_fonts_.end()) {
            loadFont(string);
            it = loaded_fonts_.find(string);
        }
        FTAssert(it != loaded_fonts_.end(), "Could not find Font %s", string.c_str());
        return it->second;
    }

protected:
    std::unordered_map<std::string, std::shared_ptr<FTFont>> loaded_fonts_;

    FTFontCache();
    ~FTFontCache();
};
