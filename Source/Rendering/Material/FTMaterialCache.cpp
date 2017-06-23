#include "FTMaterialCache.h"

NS_FT_BEGIN

FTMaterialCache::FTMaterialCache() {
    FTLOG("FTMaterialCache Init");
    loadMaterial("Default", FTMaterial());
}


FTMaterialCache::~FTMaterialCache() {
    FTLOG("FTMaterialCache destroyed");

}

NS_FT_END