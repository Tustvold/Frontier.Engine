#include "FTMaterialCache.h"

FTMaterialCache::FTMaterialCache() {
    FTLOG("FTMaterialCache Init");
    loadMaterial("Default", FTMaterial());
}


FTMaterialCache::~FTMaterialCache() {
    FTLOG("FTMaterialCache destroyed");

}
