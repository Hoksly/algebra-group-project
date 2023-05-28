#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../poly-field-math.h"
#include "../../../finite-field/source/tests/utils.h"
#include <random>
#include <vector>

using namespace modular;

TEST_CASE("Cyclotomic Polynomial Factorization") {
    for (int j = 0; j < 1000; j++)
    {
        int n = getRandomNumber(1, 100);
        int mod = 13;
        PolynomialField<int> q;
        Polynomial<int> expected; expected.fromCyclotomic(n, mod);
        std::vector<PolynomialField<int>> multipliers = q.cyclotomicToMultipliers(n, mod);
        int len = multipliers.size();
        for (int i = 1; i < len; i++)
            multipliers[0] = multipliers[0] * multipliers[i];

        CHECK_EQ(multipliers[0], expected);
    }
}