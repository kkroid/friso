#pragma once

#include "friso.h"
#include <string>

class FrisoCppWrapper
{
public:
    static FrisoCppWrapper& GetInstance();

    FrisoCppWrapper(const FrisoCppWrapper&) = delete;
    FrisoCppWrapper& operator=(const FrisoCppWrapper&) = delete;

    void Init(std::string DictFolder);
    std::vector<std::string> RunTask(std::string Text);

private:
    FrisoCppWrapper();
    ~FrisoCppWrapper();
    bool bInited = false;
    friso_t FrisoInstance;
    friso_config_t FrisoConfig;
};