#include "FrisoTest.h"
#include <locale>
#include <string>
#include <iostream>
#include <codecvt>
#include <windows.h>
#include <vector>
#include "EncodingConversion.h"

#define CONST_TO_NON_CONST(ptr) ((char*)(uintptr_t)(ptr))
#define ENCODING_FOLDER "UTF-8"
#define FRISOCHARSET FRISO_UTF8

// 将 GBK 编码的 char* 转换为 std::wstring
std::wstring GbkToWstring(const char* szGbk)
{
    int len = MultiByteToWideChar(CP_ACP, 0, szGbk, -1, NULL, 0);
    wchar_t* wszUtf8 = new wchar_t[len + 1];
    MultiByteToWideChar(CP_ACP, 0, szGbk, -1, wszUtf8, len);
    std::wstring result = wszUtf8;
    delete[] wszUtf8;
    return result;
    // std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter;
    // return converter.from_bytes(szGbk);
}

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

char* WstringToGbk(const std::wstring& wstr)
{
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    char* szGbk = new char[len + 1];
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szGbk, len, NULL, NULL);
    return szGbk;
}


FrisoTest::FrisoTest() {
    friso = friso_new();
}

FrisoTest::~FrisoTest() {
    friso_free(friso);
}

void FrisoTest::init(std::string configFile) {
    config = friso_new_config();
    config->add_syn = 0;
    friso_set_mode(config, __FRISO_COMPLEX_MODE__);
    friso_dic_t dict = friso_dic_new();
    friso->dic = dict;
    friso->charset = FRISOCHARSET;
    int _limits = config->max_len * (friso->charset == FRISO_UTF8 ? 3 : 2);
    std::string base_folder = "E:/github/friso/vendors/dict/";
    std::string dict_files[14] = { 
        base_folder + ENCODING_FOLDER + "/lex-main.lex",
        base_folder + ENCODING_FOLDER + "/lex-admin.lex",
        base_folder + ENCODING_FOLDER + "/lex-chars.lex",
        base_folder + ENCODING_FOLDER + "/lex-cn-mz.lex",
        base_folder + ENCODING_FOLDER + "/lex-cn-place.lex",
        base_folder + ENCODING_FOLDER + "/lex-company.lex",
        base_folder + ENCODING_FOLDER + "/lex-festival.lex",
        base_folder + ENCODING_FOLDER + "/lex-flname.lex",
        base_folder + ENCODING_FOLDER + "/lex-food.lex",
        base_folder + ENCODING_FOLDER + "/lex-lang.lex",
        base_folder + ENCODING_FOLDER + "/lex-nation.lex",
        base_folder + ENCODING_FOLDER + "/lex-net.lex",
        base_folder + ENCODING_FOLDER + "/lex-org.lex",
        base_folder + ENCODING_FOLDER + "/lex-touris.lex"
    };
    for (size_t i = 0; i < 14; i++)
    {
        friso_dic_load( friso, config, __LEX_CJK_WORDS__, CONST_TO_NON_CONST(dict_files[i].c_str()), _limits );
    }

    // config = friso_new_config();
    // friso_init_from_ifile(friso, config, WstringToGbk(GbkToWstring("E:/github/friso/friso.ini")));
}

void FrisoTest::test(char *text) {
    printf("test(\"%s\")\n", text);
    friso_task_t task = friso_new_task();
    friso_set_text(task, text);
    while ( ( config->next_token( friso, config, task ) ) != NULL )
    {
        printf("%s, ", task->token->word);
    }
    printf("==============识别完毕================\n");
    friso_free_task(task);
}

int main(int argc, char const *argv[] ) {
    setlocale(LC_ALL, "en_US.UTF-8");
    FrisoTest frisoTest;
    frisoTest.init("");
    const char *argv1_gbk = WstringToUtf8(GbkToWstring(argv[1]));
    // const char *argv1_gbk = EncodingConversion::GBKToUTF8(argv[1]).c_str();
    printf("param=%s\n", argv1_gbk);
    frisoTest.test(CONST_TO_NON_CONST(argv1_gbk));
    return 0;
}