#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../mod-math.h"
#include "utils.h"
#include <gmpxx.h>

using namespace modular;

TEST_CASE("EULER_CHECK"){
    mpz_class actual [] = {1,1,2,2,4,2,6,4,6,4,10,4,12,6,8,8,16,6,18,8,12,
 10,22,8,20,12,18,12,28,8,30,16,20,16,24,12,36,18,
 24,16,40,12,42,20,24,22,46,16,42,20,32,24,52,18,
 40,24,36,28,58,16,60,30,36,32,48,20,66,32,44};
    
    for (int i = 1; i<=69; i++)
    {
        mpz_class val = EulerFunction<mpz_class>(static_cast<mpz_class>(i));

        CHECK_EQ(val, actual[i-1]);
    }
}

TEST_CASE("EULER_FROM_WOLFRAM"){
    int ans = 72;
    int res = EulerFunction<int>(111);
    CHECK_EQ(ans,res);    
}

TEST_CASE("CARMICHAEL_CHECK"){
    mpz_class actual[] = {1, 1, 2, 2, 4, 2, 6, 2, 6, 4, 10, 2, 12, 6, 4, 4, 16, 6, 18, 4, 6, 10, 22, 2, 20, 12, 18, 6, 28, 4, 30, 8, 10, 16, 12, 6, 36, 18, 12, 4, 40, 6, 42, 10, 12, 22, 46, 4, 42, 20, 16, 12, 52, 18, 20, 6, 18, 28, 58, 4, 60, 30, 6, 16, 12, 10, 66, 16, 22, 12, 70, 6, 72, 36, 20, 18, 30, 12, 78, 4, 54};
    for (int i=1; i<=81; i++){
        mpz_class value = CarmichaelFunction<mpz_class>(static_cast<mpz_class>(i));
        CHECK_EQ(value, actual[i-1]);
    }
}

