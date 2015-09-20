#pragma once

#include <Frontier.h>


class FTEventManager;
class FTFontCache;
class FTShaderCache;
class FTInputManager;
class FTDirector;

class FTEngine {
public:
    

    static FTDirector* getDirector();
    static FTInputManager* getInputManager();
    static FTShaderCache* getShaderCache();
    static FTFontCache* getFontCache();
    static FTEventManager* getEventManager();

    static bool cleanup();

    static bool setup(bool is_mocked = false);

    static void init();

private:
    static FTEngine* getSharedInstance();

    FTEngine();
    ~FTEngine();

    bool _setup(bool is_mocked);

    FTEventManager* event_manager_;
    FTFontCache* font_cache_;
    FTShaderCache* shader_cache_;
    FTInputManager* input_manager_;
    FTDirector* director_;
    bool setup_;
};
