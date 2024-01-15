#include "FrisoCppWrapper.h"
#include <time.h>


#define CONST_TO_NON_CONST(ptr) ((char*)(uintptr_t)(ptr))
#define ENCODING_FOLDER "UTF-8"
#define FRISOCHARSET FRISO_UTF8

FrisoCppWrapper::FrisoCppWrapper()
{
    FrisoInstance = friso_new();
    FrisoConfig = friso_new_config();
}

FrisoCppWrapper::~FrisoCppWrapper()
{
    friso_free_config(FrisoConfig);
    friso_free(FrisoInstance);
}

FrisoCppWrapper& FrisoCppWrapper::GetInstance()
{
    static FrisoCppWrapper instance;
    return instance;
}

void FrisoCppWrapper::Init(std::string DictFolder)
{
    if (bInited)
    {
        return;
    }
    clock_t StartTime, EndTime;
    StartTime = clock();
    bInited = true;
    FrisoConfig->add_syn = 0;
    friso_set_mode(FrisoConfig, __FRISO_COMPLEX_MODE__);
    friso_dic_t dict = friso_dic_new();
    FrisoInstance->dic = dict;
    FrisoInstance->charset = FRISOCHARSET;
    int _limits = FrisoConfig->max_len * (FrisoInstance->charset == FRISO_UTF8 ? 3 : 2);
    std::string CJK_WORDS_FILES[14] = { 
        DictFolder + ENCODING_FOLDER + "/lex-main.lex",
        DictFolder + ENCODING_FOLDER + "/lex-admin.lex",
        DictFolder + ENCODING_FOLDER + "/lex-chars.lex",
        DictFolder + ENCODING_FOLDER + "/lex-cn-mz.lex",
        DictFolder + ENCODING_FOLDER + "/lex-cn-place.lex",
        DictFolder + ENCODING_FOLDER + "/lex-company.lex",
        DictFolder + ENCODING_FOLDER + "/lex-festival.lex",
        DictFolder + ENCODING_FOLDER + "/lex-flname.lex",
        DictFolder + ENCODING_FOLDER + "/lex-food.lex",
        DictFolder + ENCODING_FOLDER + "/lex-lang.lex",
        DictFolder + ENCODING_FOLDER + "/lex-nation.lex",
        DictFolder + ENCODING_FOLDER + "/lex-net.lex",
        DictFolder + ENCODING_FOLDER + "/lex-org.lex",
        DictFolder + ENCODING_FOLDER + "/lex-touris.lex"
    };

    std::string CJK_UNITS_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-units.lex"
    };

    std::string ECM_WORDS_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-ecmixed.lex"
    };
    
    std::string CEM_WORDS_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-cemixed.lex"
    };

    std::string CN_LNAME_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-lname.lex"
    };

    std::string CN_SNAME_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-sname.lex"
    };

    std::string CN_DNAME1_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-dname-1.lex"
    };

    std::string CN_DNAME2_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-dname-2.lex"
    };

    std::string CN_LNA_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-ln-adorn.lex"
    };

    std::string STOPWORDS_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-stopword.lex"
    };

    std::string ENPUN_WORDS_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-en-pun.lex"
    };

    std::string EN_WORDS_FILES[1] = {
        DictFolder + ENCODING_FOLDER + "/lex-en.lex"
    };

    int LEN_CJK_WORDS_FILES = sizeof(CJK_WORDS_FILES) / sizeof(CJK_WORDS_FILES[0]);
    for (int i = 0; i < LEN_CJK_WORDS_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_CJK_WORDS__, CONST_TO_NON_CONST(CJK_WORDS_FILES[i].c_str()), _limits );
    }

    int LEN_CJK_UNITS_FILES = sizeof(CJK_UNITS_FILES) / sizeof(CJK_UNITS_FILES[0]);
    for (int i = 0; i < LEN_CJK_UNITS_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_CJK_UNITS__, CONST_TO_NON_CONST(CJK_UNITS_FILES[i].c_str()), _limits );
    }

    int LEN_ECM_WORDS_FILES = sizeof(ECM_WORDS_FILES) / sizeof(ECM_WORDS_FILES[0]);
    for (int i = 0; i < LEN_ECM_WORDS_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_ECM_WORDS__, CONST_TO_NON_CONST(ECM_WORDS_FILES[i].c_str()), _limits );
    }

    int LEN_CEM_WORDS_FILES = sizeof(CEM_WORDS_FILES) / sizeof(CEM_WORDS_FILES[0]);
    for (int i = 0; i < LEN_CEM_WORDS_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_CEM_WORDS__, CONST_TO_NON_CONST(CEM_WORDS_FILES[i].c_str()), _limits );
    }

    int LEN_CN_LNAME_FILES = sizeof(CN_LNAME_FILES) / sizeof(CN_LNAME_FILES[0]);
    for (int i = 0; i < LEN_CN_LNAME_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_CN_LNAME__, CONST_TO_NON_CONST(CN_LNAME_FILES[i].c_str()), _limits );
    }

    int LEN_CN_SNAME_FILES = sizeof(CN_SNAME_FILES) / sizeof(CN_SNAME_FILES[0]);
    for (int i = 0; i < LEN_CN_SNAME_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_CN_SNAME__, CONST_TO_NON_CONST(CN_SNAME_FILES[i].c_str()), _limits );
    }

    int LEN_CN_DNAME1_FILES = sizeof(CN_DNAME1_FILES) / sizeof(CN_DNAME1_FILES[0]);
    for (int i = 0; i < LEN_CN_DNAME1_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_CN_DNAME1__, CONST_TO_NON_CONST(CN_DNAME1_FILES[i].c_str()), _limits );
    }

    int LEN_CN_DNAME2_FILES = sizeof(CN_DNAME2_FILES) / sizeof(CN_DNAME2_FILES[0]);
    for (int i = 0; i < LEN_CN_DNAME2_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_CN_DNAME2__, CONST_TO_NON_CONST(CN_DNAME2_FILES[i].c_str()), _limits );
    }

    int LEN_CN_LNA_FILES = sizeof(CN_LNA_FILES) / sizeof(CN_LNA_FILES[0]);
    for (int i = 0; i < LEN_CN_LNA_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_CN_LNA__, CONST_TO_NON_CONST(CN_LNA_FILES[i].c_str()), _limits );
    }

    int LEN_STOPWORDS_FILES = sizeof(STOPWORDS_FILES) / sizeof(STOPWORDS_FILES[0]);
    for (int i = 0; i < LEN_STOPWORDS_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_STOPWORDS__, CONST_TO_NON_CONST(STOPWORDS_FILES[i].c_str()), _limits );
    }

    int LEN_ENPUN_WORDS_FILES = sizeof(ENPUN_WORDS_FILES) / sizeof(ENPUN_WORDS_FILES[0]);
    for (int i = 0; i < LEN_ENPUN_WORDS_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_ENPUN_WORDS__, CONST_TO_NON_CONST(ENPUN_WORDS_FILES[i].c_str()), _limits );
    }

    int LEN_EN_WORDS_FILES = sizeof(EN_WORDS_FILES) / sizeof(EN_WORDS_FILES[0]);
    for (int i = 0; i < LEN_EN_WORDS_FILES; i++)
    {
        friso_dic_load( FrisoInstance, FrisoConfig, __LEX_EN_WORDS__, CONST_TO_NON_CONST(EN_WORDS_FILES[i].c_str()), _limits );
    }

    EndTime = clock();
    printf("Initialized in %fsec\n", (double) ( EndTime - StartTime ) / CLOCKS_PER_SEC );
}

std::vector<std::string> FrisoCppWrapper::RunTask(std::string Text)
{
    clock_t StartTime, EndTime;
    StartTime = clock();
    friso_task_t Task = friso_new_task();
    friso_set_text( Task, CONST_TO_NON_CONST(Text.c_str()) );
    std::vector<std::string> Results;
    while ( ( FrisoConfig->next_token( FrisoInstance, FrisoConfig, Task ) ) != NULL )
    {
        Results.push_back(std::string(Task->token->word));
        // printf("[%s]\n", Task->token->word);
    }
    friso_free_task(Task);
    EndTime = clock();
    printf("RunTask:%s in %fsec\n", Text.c_str(), (double) ( EndTime - StartTime ) / CLOCKS_PER_SEC );
    return Results;
}