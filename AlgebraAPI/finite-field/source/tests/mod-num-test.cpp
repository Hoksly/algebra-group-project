#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../mod-math.h"
#include "utils.h"
#include <random>

using namespace modular;

TEST_CASE("Testing modNum class with random values")
{
    using T = int;
    const int MOD = getRandomPrimeNumber(13, 200);
     modNum<T> a(getRandomNumber(1, MOD - 1), MOD);
     modNum<T> b(getRandomNumber(1, MOD - 1), MOD);

    SUBCASE("Test addition")
    {
        modNum<T> result = a + b;
        REQUIRE(result.getValue() == (a.getValue() + b.getValue()) % MOD);
    }

    SUBCASE("Test subtraction")
    {
        modNum<T> result = a - b;
        REQUIRE(result.getValue() == (a.getValue() - b.getValue() + MOD) % MOD);
    }

    SUBCASE("Test multiplication")
    {
        modNum<T> result = a * b;
        REQUIRE(result.getValue() == (a.getValue() * b.getValue()) % MOD);
    }

    SUBCASE("Test division")
    {

        modNum<T> result = a / b;
        REQUIRE(result.getValue() * b.getValue() % MOD == a.getValue());
    }

    SUBCASE("Test inversion existence")
    {

        T notPrimeMod(90);
        modNum<T> n1(30, notPrimeMod);
        REQUIRE_THROWS_AS(n1.inv(), std::invalid_argument);
    }

    SUBCASE("Test inversion")
    {
        modNum<T> result = a.inv();
        REQUIRE(result.getValue() * a.getValue() % MOD == static_cast<T>(1));
    }
}