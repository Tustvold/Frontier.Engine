#pragma once
#include <Frontier.h>
#include <Event/Engine/FTEngineEvents.h>
#include <vector>

NS_FT_BEGIN

class Scene;
class Camera;
class ShaderCache;
class MaterialCache;
class FontCache;
class ActionManager;

// Class which manages the scene hierarchy
class Director {
    friend class Engine;
public:

    void setCurrentScene(const std::shared_ptr<Scene>& scene, bool immediately = false);

    void setCurrentScene(std::shared_ptr<Scene>&& scene, bool immediately = false);

    void pushScene(const std::shared_ptr<Scene>& scene, bool immediately = false);

    void popScene(bool immediately = false);

    ShaderCache* getShaderCache() const {
        return shader_cache_;
    }

    MaterialCache* getMaterialCache() const {
        return material_cache_;
    }

    FontCache* getFontCache() const {
        return font_cache_;
    }

    ActionManager* getActionManager() const {
        return action_manager_;
    }

private:
    Director();
    ~Director();

    void setup();

    void cleanup();

    void draw(const DrawEvent& event);

    void exchangeScenes();

    void preTick(const PreTickEvent& event);

    ShaderCache* shader_cache_;
    MaterialCache* material_cache_;
    FontCache* font_cache_;
    ActionManager* action_manager_;

    std::shared_ptr<Scene> scene_;
    std::shared_ptr<Scene> next_scene_;
    bool push_previous_scene_;

    std::vector<std::shared_ptr<Scene>> paused_scenes_;

    double fps_time_acc_;
};

NS_FT_END