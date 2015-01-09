#pragma once

#include "Frontier.h"
#include <string>
#include <xstring>
#include "FTArray.h"
#include <sstream>


// Supports char and wchar_t
// Unfortunately Visual C++ doesn't properly support Unicode literals
// And so we are stuck with the evil wchar_t
template <typename CharacterType> class FTStringUtil{

};

template <> class FTStringUtil<wchar_t> {
public:
	static wchar_t* formatString(wchar_t* buff, size_t buf_size, wchar_t* format...) {
		va_list args;
		va_start(args, format);
		vswprintf_s((wchar_t*)buff, buf_size, format, args);
		va_end(args);
		return buff;
	}
};

template <> class FTStringUtil<char>{
public:
	static char* formatString(char* buff, size_t buf_size, char* format...) {
		va_list args;
		va_start(args, format);
		vsprintf_s(buff, buf_size, format, args);
		va_end(args);
		return buff;
	}
};

template <typename CharacterType> class FTString : public FTObject {
public:
	typedef std::basic_string<CharacterType> StandardString;

	explicit FTString(StandardString string) : string_(string) {

	}

	explicit FTString(const CharacterType* string) : string_(string) {
		
	}

	/*static FTString* newFromCharString(const char* string) {
		std::wstring_convert<std::codecvt<CharacterType, char, std::mbstate_t>, CharacterType> convert;
		return new FTString(convert.from_bytes(string));
	}*/

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
	

	StandardString string_;
	std::hash<std::basic_string<CharacterType>> hasher_;
};
