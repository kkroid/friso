
#include <string>
#include "friso.h"

class FrisoTest {
public:
    FrisoTest();
    ~FrisoTest();
    void init(std::string config);
    void test(char *text);

private:
    friso_t friso;
    friso_config_t config;
};