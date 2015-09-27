#include "FTEngine.h"

#include "Rendering/FTDirector.h"
#include "Event/Input/FTInputManager.h"
#include "Rendering/Shader/FTShaderCache.h"
#include "Rendering/Text/FTFontCache.h"
#include "Event/FTEventManager.h"

static FTEngine* s_instance = nullptr;

FTEngine* FTEngine::getSharedInstance() {
    FTAssert(s_instance != nullptr, "Please call FTEngine::setup() first");
    return s_instance;
}

FTEngine::FTEngine() : setup_(false) {
    director_ = new FTDirector();
    event_manager_ = new FTEventManager();
    input_manager_ = new FTInputManager();
    shader_cache_ = new FTShaderCache();
    font_cache_ = new FTFontCache();
}

FTEngine::~FTEngine() {
    delete director_;
    delete input_manager_;
    delete shader_cache_;
    delete font_cache_;
    delete event_manager_;
}

bool FTEngine::_setup(bool is_mocked) {
    if (!is_mocked && director_->setup() != 0) {
        FTLog("Director initialisation failed");
        return false;
    }

    input_manager_->setup();

    return true;
}


bool FTEngine::setup(bool is_mocked) {
    if (s_instance == nullptr) {
        FTEngine::init();
    }
    FTAssert(!s_instance->setup_, "FTEngine already setup");
    if (s_instance->_setup(is_mocked)) {
        return true;
    }
    cleanup();
    return false;
}

void FTEngine::init() {
    FTAssert(s_instance == nullptr, "FTEngine::init() already called");
    s_instance = new FTEngine();
}

bool FTEngine::cleanup() {
    if (s_instance == nullptr)
        return true;
    delete s_instance;
    s_instance = nullptr;
    return true;
}

FTDirector* FTEngine::getDirector() {
    return getSharedInstance()->director_;
}

FTInputManager* FTEngine::getInputManager() {
    return getSharedInstance()->input_manager_;
}

FTShaderCache* FTEngine::getShaderCache() {
    return getSharedInstance()->shader_cache_;
}

FTFontCache* FTEngine::getFontCache() {
    return getSharedInstance()->font_cache_;
}

FTEventManager* FTEngine::getEventManager() {
    return getSharedInstance()->event_manager_;
}