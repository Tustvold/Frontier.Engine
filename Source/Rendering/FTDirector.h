#pragma once
#include <Frontier.h>
#include <Event/Engine/FTEngineEvents.h>

class FTScene;
class FTCamera;
class FTShaderCache;
class FTFontCache;
class FTActionManager;

// Class which manages the scene hierarchy
class FTDirector {
    friend class FTEngine;
public:

    void setCurrentScene(const std::shared_ptr<FTScene>& scene);

    FTShaderCache* getShaderCache() const {
        return shader_cache_;
    }

    FTFontCache* getFontCache() const {
        return font_cache_;
    }

    FTActionManager* getActionManager() const {
        return action_manager_;
    }

private:
    FTDirector();
    ~FTDirector();

    void setup();

    void cleanup();

    void draw(const FTDrawEvent& event);


    FTShaderCache* shader_cache_;
    FTFontCache* font_cache_;
    FTActionManager* action_manager_;

    std::shared_ptr<FTScene> scene_;

    double fps_time_acc_;
};
