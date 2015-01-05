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

#ifdef DEBUG_FT_ALLOC
		if (FTObject::ft_object_alive_count_ != 0) {
			FTLogError("Failed to deallocate all FTObjects - %i still alive", FTObject::ft_object_alive_count_.load());
		}
		else {
			FTLog("All FTObjects deallocated correctly!");
		}
#endif
	}
private:
	static void cleanupSingletons() {
		delete FTInputManager::getSharedInstance();
		delete FTShaderCache::getSharedInstance();
		delete FTDirector::getSharedInstance();
		delete FTFontCache::getSharedInstance();
	}
};