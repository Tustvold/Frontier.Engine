#include "FTDirector.h"
#include <Frontier.h>
#include <FTEngine.h>
#include <Event/Engine/FTEngineEventDispatcher.h>
#include <Event/FTEventManager.h>
#include <Rendering/FTScene.h>
#include "Rendering/Action/FTActionManager.h"
#include "Text/FTFontCache.h"

void FTDirector::setCurrentScene(const std::shared_ptr<FTScene>& scene) {
    if (scene_)
        scene_->onExit();
    scene_ = scene;
    scene_->onEnter();
}

FTDirector::FTDirector() : shader_cache_(nullptr), font_cache_(nullptr), action_manager_(nullptr), fps_time_acc_(0) {
}


FTDirector::~FTDirector() {
    FTLOG("Director destroyed");
    delete action_manager_;
    delete font_cache_;
    delete shader_cache_;
}

void FTDirector::setup() {
    shader_cache_ = new FTShaderCache();
    font_cache_ = new FTFontCache();
    action_manager_ = new FTActionManager();

    FTEngine::getEventManager()->registerDelegate<FTEngineEventDispatcher>(this, &FTDirector::draw);
}

void FTDirector::cleanup() {
    if (scene_)
        scene_->onExit();
    scene_.reset();
    FTEngine::getEventManager()->unregisterDelegate<FTEngineEventDispatcher>(this, &FTDirector::draw);
}

void FTDirector::draw(const FTDrawEvent& event) {
    glDisable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SCISSOR_TEST);

    scene_->visit();
    scene_->draw();

    glfwSwapBuffers(event.window_);
}
