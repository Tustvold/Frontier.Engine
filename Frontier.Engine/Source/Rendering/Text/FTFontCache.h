#pragma once
#include <Rendering/Text/FTFont.h>
#include <FTDictionary.h>

class FTFontCache {
	friend class FTEngine;
public:
	static FTFontCache* getSharedInstance();

	bool loadFont(const char* name);

	FTFont* getFont(const char* string) {
		FTString<char> tester(string);
		return loaded_fonts_->get(&tester);
	}

protected:
	FTDictionary<FTString<char>, FTFont>* loaded_fonts_;
	
	FTFontCache();
	~FTFontCache();
};
