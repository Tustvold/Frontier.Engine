#include "FTDirector.h"
#include <Frontier.h>
#include <FTEngine.h>
#include <Event/Engine/FTEngineEventDispatcher.h>
#include <Event/FTEventManager.h>
#include <Rendering/FTScene.h>
#include "Rendering/Action/FTActionManager.h"
#include "Text/FTFontCache.h"

void FTDirector::pushScene(const std::shared_ptr<FTScene>& scene, bool immediately) {
    FTAssert(next_scene_ == nullptr, "FTDirector already transitioning between scenes");
    next_scene_ = scene;
    push_previous_scene_ = true;
    if (immediately)
        exchangeScenes();
}

void FTDirector::popScene(bool immediately) {
    FTAssert(paused_scenes_.size() != 0, "No parent scenes to resume");
    next_scene_ = std::move(paused_scenes_.back());
    paused_scenes_.pop_back();
    push_previous_scene_ = false;
    if (immediately)
        exchangeScenes();
}

void FTDirector::setCurrentScene(const std::shared_ptr<FTScene>& scene, bool immediately) {
    FTAssert(next_scene_ == nullptr, "FTDirector already transitioning between scenes");
    next_scene_ = scene;
    push_previous_scene_ = false;
    if (immediately)
        exchangeScenes();
}

void FTDirector::setCurrentScene(std::shared_ptr<FTScene>&& scene, bool immediately) {
    FTAssert(next_scene_ == nullptr, "FTDirector already transitioning between scenes");
    next_scene_ = std::move(scene);
    push_previous_scene_ = false;
    if (immediately)
        exchangeScenes();
}

FTDirector::FTDirector() : shader_cache_(nullptr), font_cache_(nullptr), action_manager_(nullptr), push_previous_scene_(false), fps_time_acc_(0) {
}


FTDirector::~FTDirector() {
    FTLOG("Director destroyed");
    delete action_manager_;
    delete font_cache_;
    delete shader_cache_;
}

void FTDirector::setup() {
    shader_cache_ = new FTShaderCache();
    material_cache_ = new FTMaterialCache();
    font_cache_ = new FTFontCache();
    action_manager_ = new FTActionManager();

    FTEngine::getEventManager()->registerDelegate<FTEngineEventDispatcher>(this, &FTDirector::draw);
    FTEngine::getEventManager()->registerDelegate<FTEngineEventDispatcher>(this, &FTDirector::preTick);
}

void FTDirector::cleanup() {
    if (scene_)
        scene_->onExit();
    scene_.reset();
    FTEngine::getEventManager()->unregisterDelegate<FTEngineEventDispatcher>(this, &FTDirector::draw);
    FTEngine::getEventManager()->unregisterDelegate<FTEngineEventDispatcher>(this, &FTDirector::preTick);
}

void FTDirector::draw(const FTDrawEvent& event) {
    glDisable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);

    scene_->visit();
    scene_->draw();

    glfwSwapBuffers(event.window_);
}

void FTDirector::exchangeScenes() {
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

void FTDirector::preTick(const FTPreTickEvent& event) {
    exchangeScenes();
}
