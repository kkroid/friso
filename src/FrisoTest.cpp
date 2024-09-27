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
    // 检测是否为合法的ASCII字符
    bool isAscii = true;
    for (char ch : str) {
        if (((unsigned char)ch) > 127) {
            isAscii = false;
            break;
        }
    }

    if (isAscii) {
        return "ASCII";
    }

    // 检测是否为UTF-8编码
    bool isUtf8 = true;
    int numBytes = 0;

    for (char ch : str) {
        if (numBytes == 0) {
            if ((ch & 0b10000000) == 0) {
                continue;
            } else if ((ch & 0b11100000) == 0b11000000) {
                numBytes = 1;
            } else if ((ch & 0b11110000) == 0b11100000) {
                numBytes = 2;
            } else if ((ch & 0b11111000) == 0b11110000) {
                numBytes = 3;
            } else {
                isUtf8 = false;
                break;
            }
        } else {
            if ((ch & 0b11000000) != 0b10000000) {
                isUtf8 = false;
                break;
            }
            numBytes--;
        }
    }

    if (isUtf8) {
        return "UTF-8";
    }

    // 默认认为是GBK编码
    return "GBK";
}

int main(int argc, char const *argv[] ) {
    setlocale(LC_ALL, "en_US.UTF-8");
    FrisoCppWrapper::GetInstance().Init("E:/github/friso/vendors/dict/");
    std::string text = std::string(argv[1] == nullptr ? "你真是个不错的小伙子" : argv[1]);
    std::string encoding = detectEncoding(text);
    printf("文本编码:%s\n", encoding.c_str());
    if (encoding != "UTF-8")
    {
        text = std::string(WstringToUtf8(GbkToWstring(text.c_str())));
        printf("转编码后的文本:%s\n", text.c_str());
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