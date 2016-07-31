#pragma once
#include <Frontier.h>
#include <vector>

class FTWCharUtil {
public:
    static wchar_t* formatString(wchar_t* buff, size_t buf_size, const wchar_t* format...);

    static std::wstring convertString(const std::string& from);

    static void toLowerCase(std::wstring& string);

    static void replaceAll(std::wstring& str, const std::wstring& from, const std::wstring& to);

    static std::vector<std::wstring> splitString(const std::wstring& str, wchar_t delim);
};

class FTCharUtil {
public:
    static char* formatString(char* buff, size_t buf_size, const char* format...);

    static std::string convertString(const std::wstring& from);

    static void toLowerCase(std::string& string);

    static void replaceAll(std::string& str, const std::string& from, const std::string& to);

    static std::vector<std::string> splitString(const std::string& str, char delim);
};
