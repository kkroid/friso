#include "FrisoTest.h"
#include <locale>
#include <string>
#include <iostream>
#include <codecvt>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include "FrisoCppWrapper.h"
// #include "EncodingConversion.h"

#define CONST_TO_NON_CONST(ptr) ((char*)(uintptr_t)(ptr))
#define ENCODING_FOLDER "UTF-8"
#define FRISOCHARSET FRISO_UTF8

#ifdef _MSC_VER
// 将 GBK 编码的 char* 转换为 std::wstring
std::wstring GbkToWstring(const char* szGbk)
{
    int len = MultiByteToWideChar(CP_ACP, 0, szGbk, -1, NULL, 0);
    wchar_t* wszUtf8 = new wchar_t[len + 1];
    MultiByteToWideChar(CP_ACP, 0, szGbk, -1, wszUtf8, len);
    std::wstring result = wszUtf8;
    delete[] wszUtf8;
    return result;
}
#endif

// 将 std::wstring 转换为 UTF-8 编码的 char*
const char* WstringToUtf8(const std::wstring& wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string narrow = converter.to_bytes(wstr);
    char* cstr = new char[narrow.length() + 1];
    strcpy(cstr, narrow.c_str());
    return cstr;
	// std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	// return convert.to_bytes(wstr.data(), wstr.data() + wstr.size()).c_str();
}

#ifdef _MSC_VER
char* WstringToGbk(const std::wstring& wstr)
{
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    char* szGbk = new char[len + 1];
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szGbk, len, NULL, NULL);
    return szGbk;
}
#endif

#include <string>

std::string detectEncoding(const std::string& str) {
    if (str.empty()) {
        return "Unknown";
    }

    if (static_cast<unsigned char>(str[0]) >= 0x80) {
        return "UTF-8";
    }

    bool isGBK = true;
    bool isUTF8 = false;

    for (size_t i = 0; i < str.length(); ++i) {
        if (static_cast<unsigned char>(str[i]) >= 0x80) {
            isGBK = false;

            if (str[i] >= 0xC0 && str[i] <= 0xDF) {
                isUTF8 = true;
            } else if (str[i] >= 0xE0 && str[i] <= 0xEF) {
                if (i + 1 < str.length() && (str[i + 1] & 0xC0) == 0x80) {
                    isUTF8 = true;
                }
            } else if (str[i] >= 0xF0 && str[i] <= 0xF7) {
                if (i + 2 < str.length() && (str[i + 1] & 0xC0) == 0x80 && (str[i + 2] & 0xC0) == 0x80) {
                    isUTF8 = true;
                }
            }

            if (isUTF8) {
                break;
            }
        }
    }

    if (isUTF8) {
        return "UTF-8";
    } else if (isGBK) {
        return "GBK";
    } else {
        return "Unknown";
    }
}

int main(int argc, char const *argv[] ) {
    setlocale(LC_ALL, "en_US.UTF-8");
    FrisoCppWrapper::GetInstance().Init("/Users/willzhang/github/friso/vendors/dict/");
    std::string text = std::string(argv[1] == nullptr ? "你真是个不错的小伙子" : argv[1]);
    std::string encoding = detectEncoding(text);
    printf("文本编码:%s\n", encoding.c_str());
    if (encoding != "UTF-8")
    {
    // const char *argv1_gbk = WstringToUtf8(GbkToWstring(argv[1]));
    // const char *argv1_gbk = EncodingConversion::GBKToUTF8(argv[1]).c_str();
    }
    std::vector<std::string> Results = FrisoCppWrapper::GetInstance().RunTask(text);
    for (int i = 0; i < Results.size(); i++)
    {
        printf("%s, ", Results[i].c_str());
    }
    printf("\n");
    return 0;
}