#include "FTFontCache.h"
#include "Frontier.h"

FTFontCache* FTFontCache::getSharedInstance() {
	static FTFontCache* instance = new FTFontCache();
	return instance;
}

FTFontCache::FTFontCache() : loaded_fonts_(new FTDictionary<FTString<char>,FTFont>()) {
	FTLOG("FTFontCache Init");
}

FTFontCache::~FTFontCache() {
	FTLOG("FTFontCache Destroyed");
	loaded_fonts_->release();
}

bool FTFontCache::loadFont(const char* filename) {
	auto string = new FTString<char>(filename);
	if (loaded_fonts_->contains(string)) {
		string->release();
		return false;
	}
	FTFont* font = new FTFont(string);
	loaded_fonts_->add(string, font);
	string->release();
	font->release();
	return true;
}