#include "StringUtils.h"
#include <memory.h>
#include <wchar.h>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <codecvt>
#include <locale>

NS_FT_BEGIN

wchar_t* WCharUtil::formatString(wchar_t* buff, std::size_t buf_size, const wchar_t* format...) {
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


std::wstring WCharUtil::convertString(const std::string& from) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(from);
}

void WCharUtil::toLowerCase(std::wstring& string) {
    std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}

void WCharUtil::replaceAll(std::wstring& str, const std::wstring& from, const std::wstring& to) {
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

std::vector<std::wstring> WCharUtil::splitString(const std::wstring& str, wchar_t delim) {
    std::vector<std::wstring> ret;
    std::wstringstream ss(str);
    std::wstring item;
    while (std::getline(ss, item, delim)) {
        ret.push_back(item);
    }
    return ret;
}

std::string CharUtil::convertString(const std::wstring& from) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(from);
}

void CharUtil::toLowerCase(std::string& string) {
    std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}

void CharUtil::replaceAll(std::string& str, const std::string& from, const std::string& to) {
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

std::vector<std::string> CharUtil::splitString(const std::string& str, char delim) {
    std::vector<std::string> ret;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delim)) {
        ret.push_back(item);
    }
    return ret;
}

char* CharUtil::formatString(char* buff, std::size_t buf_size, const char* format, ...) {
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

NS_FT_END
