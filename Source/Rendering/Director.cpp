#include "Director.h"
#include <Frontier.h>
#include <Engine.h>
#include <Event/Engine/EngineEventDispatcher.h>
#include <Event/EventManager.h>
#include <Rendering/Scene.h>
#include "Rendering/Action/ActionManager.h"
#include "Rendering/Text/FontCache.h"

NS_FT_BEGIN

void Director::pushScene(const std::shared_ptr<Scene>& scene, bool immediately) {
    FTAssert(next_scene_ == nullptr, "Director already transitioning between scenes");
    next_scene_ = scene;
    push_previous_scene_ = true;
    if (immediately)
        exchangeScenes();
}

void Director::popScene(bool immediately) {
    FTAssert(paused_scenes_.size() != 0, "No parent scenes to resume");
    next_scene_ = std::move(paused_scenes_.back());
    paused_scenes_.pop_back();
    push_previous_scene_ = false;
    if (immediately)
        exchangeScenes();
}

void Director::setCurrentScene(const std::shared_ptr<Scene>& scene, bool immediately) {
    FTAssert(next_scene_ == nullptr, "Director already transitioning between scenes");
    next_scene_ = scene;
    push_previous_scene_ = false;
    if (immediately)
        exchangeScenes();
}

void Director::setCurrentScene(std::shared_ptr<Scene>&& scene, bool immediately) {
    FTAssert(next_scene_ == nullptr, "Director already transitioning between scenes");
    next_scene_ = std::move(scene);
    push_previous_scene_ = false;
    if (immediately)
        exchangeScenes();
}

Director::Director() : shader_cache_(nullptr), font_cache_(nullptr), action_manager_(nullptr), push_previous_scene_(false), fps_time_acc_(0) {
}


Director::~Director() {
    FTLOG("Director destroyed");
    delete action_manager_;
    delete font_cache_;
    delete shader_cache_;
}

void Director::setup() {
    shader_cache_ = new ShaderCache();
    material_cache_ = new MaterialCache();
    font_cache_ = new FontCache();
    action_manager_ = new ActionManager();

    Engine::getEventManager()->registerDelegate<EngineEventDispatcher>(this, &Director::draw);
    Engine::getEventManager()->registerDelegate<EngineEventDispatcher>(this, &Director::preTick);
}

void Director::cleanup() {
    if (scene_)
        scene_->onExit();
    scene_.reset();
    Engine::getEventManager()->unregisterDelegate<EngineEventDispatcher>(this, &Director::draw);
    Engine::getEventManager()->unregisterDelegate<EngineEventDispatcher>(this, &Director::preTick);
}

void Director::draw(const DrawEvent& event) {
    glDisable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);

    scene_->visit();
    scene_->draw();

    glfwSwapBuffers(event.window_);
}

void Director::exchangeScenes() {
    if (next_scene_ == nullptr)
        return;
    if (scene_) {
        scene_->onExit();
        if (push_previous_scene_) {
            paused_scenes_.push_back(std::move(scene_));
        }
    }
    scene_ = std::move(next_scene_);
    scene_->onEnter();
}

void Director::preTick(const PreTickEvent& event) {
    exchangeScenes();
}

NS_FT_END