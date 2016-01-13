#pragma once
#include "Frontier.h"

template <typename CharacterType>
class FTStringUtil {

};

template <>
class FTStringUtil<wchar_t> {
public:
    static wchar_t* formatString(wchar_t* buff, size_t buf_size, const wchar_t* format...) {
        va_list args;
        va_start(args, format);
        
#ifdef WIN32
        vswprintf_s(buff, buf_size, format, args);
#else
        vswprintf(buff, buf_size, format, args);
#endif
        va_end(args);
        return buff;
    }

    static std::wstring convertString(const std::string& from) {
        std::wstring ret;
        mbstate_t mbs;
        wchar_t buffer[32];
        const char* source = from.c_str();
        // Initialize mbs
        memset(&mbs, 0, sizeof(mbs));

        size_t written_bytes;
        do {
            
#ifdef WIN32
            mbsrtowcs_s(&written_bytes, buffer, 32, &source, 31, &mbs);
#else
            written_bytes = mbsrtowcs(buffer, &source, 32, &mbs);
#endif

            ret.append(buffer, buffer[written_bytes - 1] == 0 ? written_bytes - 1 : written_bytes);
        } while (written_bytes == 32);

        return ret;
    }

    
};

template <>
class FTStringUtil<char> {
public:
    static char* formatString(char* buff, size_t buf_size, const char* format...) {
        va_list args;
        va_start(args, format);
#ifdef WIN32
        vsprintf_s(buff, buf_size, format, args);
#else
        vsprintf(buff, format, args);
#endif
        va_end(args);
        return buff;
    }

    static std::string convertString(const std::wstring& from) {
        std::string ret;
        mbstate_t mbs;
        char buffer[32];

        const wchar_t* source = from.c_str();

        // Initialize mbs
        memset(&mbs, 0, sizeof(mbs));

        size_t written_bytes;
        do {
#ifdef WIN32
            wcsrtombs_s(&written_bytes, buffer, 32, &source, 31, &mbs);
#else
            written_bytes = wcsrtombs(buffer, &source, 32, &mbs);
#endif            
            // Don't append superfluous null terminators
            ret.append(buffer, buffer[written_bytes-1] == 0 ? written_bytes-1 : written_bytes);
        } while (written_bytes == 32);
        return ret;
    }
};
