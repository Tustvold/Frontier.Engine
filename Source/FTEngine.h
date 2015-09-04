#include <Frontier.h>
#include "Rendering/FTDirector.h"
#include "Rendering/Text/FTFontCache.h"
#include "Rendering/Shader/FTShaderCache.h"
#include "Util/FTInputManager.h"

class FTEngine {
public:
    static bool setup() {
        if (FTDirector::getSharedInstance()->setup() != 0) {
            FTLog("Director initialisation failed");
            return false;
        }
        return true;
    }

    static void cleanup() {
        cleanupSingletons();
    }

private:
    static void cleanupSingletons() {
        delete FTDirector::getSharedInstance(); // Must be first
        delete FTInputManager::getSharedInstance();
        delete FTShaderCache::getSharedInstance();
        delete FTFontCache::getSharedInstance();
    }
};
