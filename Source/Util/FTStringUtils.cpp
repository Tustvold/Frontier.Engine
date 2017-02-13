#include "FTStringUtils.h"
#include <memory.h>
#include <wchar.h>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <codecvt>
#include <locale>


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
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(from);
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
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(from);
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

