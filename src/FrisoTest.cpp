#include "FrisoTest.h"

#define CONST_TO_NON_CONST(ptr) ((char*)(uintptr_t)(ptr))

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
    int _limits = config->max_len * (friso->charset == FRISO_UTF8 ? 3 : 2);
    std::string dict_files[14] = { 
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-main.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-admin.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-chars.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-cn-mz.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-cn-place.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-company.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-festival.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-flname.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-food.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-lang.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-nation.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-net.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-org.lex",
        "/Users/willzhang/github/friso/vendors/dict/UTF-8/lex-touris.lex"
    };
    for (size_t i = 0; i < 14; i++)
    {
        friso_dic_load( friso, config, __LEX_CJK_WORDS__, CONST_TO_NON_CONST(dict_files[i].c_str()), _limits );
    }

}

void FrisoTest::test() {
    friso_task_t task = friso_new_task();
    char *text = "关于登山我喜欢爬泰山和嵩山";
    friso_set_text(task, text);
    while ( ( config->next_token( friso, config, task ) ) != NULL ) {
        printf("%s, ", task->token->word);
    }
    println("");
    friso_free_task(task);
}

int main() {
    FrisoTest frisoTest;
    frisoTest.init("");
    frisoTest.test();
    return 0;
}