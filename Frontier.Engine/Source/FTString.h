//
//  FTString.h
//  Frontier
//
//  Created by Raphael Taylor-Davies on 10/06/2014.
//  Copyright (c) 2014 Subterranean Software. All rights reserved.
//

#pragma once

#include "Frontier.h"
#include <string>
#include <xstring>
#include <codecvt>
#include "FTArray.h"
#include <sstream>


template <typename CharacterType> class FTString : public FTObject {
public:
	typedef std::basic_string<CharacterType> StandardString;

	explicit FTString(StandardString string) : string_(string) {

	}

	/*explicit FTString(const CharacterType* string...) {
		va_list args;
		va_start(args,string);
		setFormat(string, args);
		va_end(args);
	}*/

	explicit FTString(const CharacterType* string) : string_(string) {
		
	}

	static FTString* createNewFromCharString(const char* string) {
		std::wstring_convert<std::codecvt<CharacterType, char, std::mbstate_t>, CharacterType> convert;
		return new FTString(convert.from_bytes(string));
	}

	virtual bool isEqual(const FTObject* a) const override {
		const FTString<CharacterType>* string = static_cast<const FTString<CharacterType>*>(a);
		if (string == nullptr)
			return false;

		if (a == this)
			return true;

		return string->getString() == string_;
	}

	virtual size_t hash() const override {
		return hasher_(string_);
	}

	const StandardString& getString() const {
		return string_;
	}

	const CharacterType* getCString() const {
		return string_.c_str();
	}

	void append(StandardString& string) {
		string_.append(string);
	}

	FTArray<FTString>* split(const CharacterType* delimiter, size_t delimiterLength) {
		StandardString to_split = string_;
		FTArray<FTString>* strings = new FTArray<FTString>();
		size_t pos = 0;
		while ((pos = to_split.find(delimiter)) != StandardString::npos) {
			StandardString split = to_split.substr(0, pos);
			FTString* str = new FTString(split);
			strings->add(str);
			str->release();
			to_split.erase(0, pos + delimiterLength);
		}
		FTString* str = new FTString(to_split);
		strings->add(str);
		str->release();

		return strings;
	}
private:
	static_assert(sizeof(wchar_t) == 2, "FTString requires wchar_t be 2 bytes in size");

	StandardString string_;
	std::hash<std::basic_string<CharacterType>> hasher_;

	/*void setFormat(const CharacterType* string, va_list list) {
		const size_t maxSize = 1024;
		CharacterType buff[maxSize];
		if (sizeof(CharacterType) == 2)
			vswprintf(buff, maxSize, (const wchar_t*)string, list);
		else
			vsprintf(buff, maxSize, (const char*) string, list);
		string_ = (const CharacterType *)buff;
	}*/
};
