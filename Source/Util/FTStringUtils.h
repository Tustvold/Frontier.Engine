#pragma once
#include "Frontier.h"


// Supports char and wchar_t
// Unfortunately Visual C++ doesn't properly support Unicode literals
// And so we are stuck with the evil wchar_t
template <typename CharacterType>
class FTStringUtil {

};

template <>
class FTStringUtil<wchar_t> {
public:
    static wchar_t* formatString(wchar_t* buff, size_t buf_size, wchar_t* format...) {
        va_list args;
        va_start(args, format);
        vswprintf_s((wchar_t*)buff, buf_size, format, args);
        va_end(args);
        return buff;
    }
};

template <>
class FTStringUtil<char> {
public:
    static char* formatString(char* buff, size_t buf_size, char* format...) {
        va_list args;
        va_start(args, format);
        vsprintf_s(buff, buf_size, format, args);
        va_end(args);
        return buff;
    }
};
