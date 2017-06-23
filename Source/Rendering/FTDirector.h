#pragma once
#include <Frontier.h>
#include <Event/Engine/FTEngineEvents.h>
#include <vector>

NS_FT_BEGIN

class FTScene;
class FTCamera;
class FTShaderCache;
class FTMaterialCache;
class FTFontCache;
class FTActionManager;

// Class which manages the scene hierarchy
class FTDirector {
    friend class FTEngine;
public:

    void setCurrentScene(const std::shared_ptr<FTScene>& scene, bool immediately = false);

    void setCurrentScene(std::shared_ptr<FTScene>&& scene, bool immediately = false);

    void pushScene(const std::shared_ptr<FTScene>& scene, bool immediately = false);

    void popScene(bool immediately = false);

    FTShaderCache* getShaderCache() const {
        return shader_cache_;
    }

    FTMaterialCache* getMaterialCache() const {
        return material_cache_;
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

    void exchangeScenes();

    void preTick(const FTPreTickEvent& event);

    FTShaderCache* shader_cache_;
    FTMaterialCache* material_cache_;
    FTFontCache* font_cache_;
    FTActionManager* action_manager_;

    std::shared_ptr<FTScene> scene_;
    std::shared_ptr<FTScene> next_scene_;
    bool push_previous_scene_;

    std::vector<std::shared_ptr<FTScene>> paused_scenes_;

    double fps_time_acc_;
};

NS_FT_END