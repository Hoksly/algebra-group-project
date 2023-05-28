#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "utils.h"
#include <random>

#include "../../../doctest.h"
#include "../../mod-math.h"

using namespace modular;

TEST_CASE("randomized test 1..1000 with mod 13")
{
    for (int i = 0; i < 1000; ++i)
    {
        int num = getRandomNumber(1, 1000);
        int pw = getRandomNumber(1, 1000);

        CHECK_EQ(fpow(modNum(num, 13), pw).getValue(), logPow(num, pw, 13));
    }
}
