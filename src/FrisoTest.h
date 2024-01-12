
#include <string>
#include "friso.h"

class FrisoTest {
public:
    FrisoTest();
    ~FrisoTest();
    void init(std::string config);
    void test();

private:
    friso_t friso;
    friso_config_t config;
};