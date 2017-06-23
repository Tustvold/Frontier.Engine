#include "MaterialCache.h"

NS_FT_BEGIN

MaterialCache::MaterialCache() {
    FTLOG("MaterialCache Init");
    loadMaterial("Default", Material());
}


MaterialCache::~MaterialCache() {
    FTLOG("MaterialCache destroyed");

}

NS_FT_END