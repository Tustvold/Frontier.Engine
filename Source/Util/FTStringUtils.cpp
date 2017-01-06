#include "FTStringUtils.h"
#include <memory.h>
#include <wchar.h>
#include <algorithm>
#include <cctype>
#include <sstream>


wchar_t* FTWCharUtil::formatString(wchar_t* buff, std::size_t buf_size, const wchar_t* format...) {
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


std::wstring FTWCharUtil::convertString(const std::string& from) {
    std::wstring ret;
    mbstate_t mbs;
    wchar_t buffer[32];
    const char* source = from.c_str();
    // Initialize mbs
    memset(&mbs, 0, sizeof(mbs));

    std::size_t written_bytes;
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

void FTWCharUtil::toLowerCase(std::wstring& string) {
    std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}

void FTWCharUtil::replaceAll(std::wstring& str, const std::wstring& from, const std::wstring& to) {
    std::size_t index = 0;
    auto to_c = to.c_str();
    while (true) {
        index = str.find(from, index);
        if (index == std::wstring::npos)
            break;

        str.replace(index, from.size(), to_c);

        index += to.size();
    }
}

std::vector<std::wstring> FTWCharUtil::splitString(const std::wstring& str, wchar_t delim) {
    std::vector<std::wstring> ret;
    std::wstringstream ss(str);
    std::wstring item;
    while (std::getline(ss, item, delim)) {
        ret.push_back(item);
    }
    return ret;
}

std::string FTCharUtil::convertString(const std::wstring& from) {
    std::string ret;
    mbstate_t mbs;
    char buffer[32];

    const wchar_t* source = from.c_str();

    // Initialize mbs
    memset(&mbs, 0, sizeof(mbs));

    std::size_t written_bytes;
    do {
#ifdef WIN32
        wcsrtombs_s(&written_bytes, buffer, 32, &source, 31, &mbs);
#else
            written_bytes = wcsrtombs(buffer, &source, 32, &mbs);
#endif 
        // Don't append superfluous null terminators
        ret.append(buffer, buffer[written_bytes - 1] == 0 ? written_bytes - 1 : written_bytes);
    } while (written_bytes == 32);
    return ret;
}

void FTCharUtil::toLowerCase(std::string& string) {
    std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}

void FTCharUtil::replaceAll(std::string& str, const std::string& from, const std::string& to) {
    size_t index = 0;
    auto to_c = to.c_str();
    while (true) {
        index = str.find(from, index);
        if (index == std::string::npos)
            break;

        str.replace(index, from.size(), to_c);

        index += to.size();
    }
}

std::vector<std::string> FTCharUtil::splitString(const std::string& str, char delim) {
    std::vector<std::string> ret;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delim)) {
        ret.push_back(item);
    }
    return ret;
}

char* FTCharUtil::formatString(char* buff, std::size_t buf_size, const char* format, ...) {
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
