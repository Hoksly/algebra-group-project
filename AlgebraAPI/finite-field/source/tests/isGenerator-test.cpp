#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <random>

#include "../../../doctest.h"
#include "../../mod-math.h"
#include "utils.h"
using namespace modular;

TEST_CASE("simple tests") {
    CHECK(isGenerator(modNum<int>(3, 7)));
    CHECK(isGenerator(modNum<int>(5, 7)));
    CHECK(!isGenerator(modNum<int>(2, 7)));

    CHECK(!isGenerator(modNum<int>(1, 7)));
    CHECK(!isGenerator(modNum<int>(4, 7)));
    CHECK(!isGenerator(modNum<int>(6, 7)));
}

TEST_CASE("random tests") {
    const int num_tests = 100;
    const int mod = 31;   // use a prime number for the modulo

    for (int i = 0; i < num_tests; ++i) {
        modNum<int> a(6, mod);

        if (a.getValue() == 0)
            continue;

        modNum<int> curEl = a;
        set<int> numbers;
        do {
            curEl = curEl * a;
            numbers.insert(curEl.getValue());
        } while (curEl.getValue() != a.getValue());

        bool is_generator = isGenerator(modNum<int>(a.getValue(), mod));

        REQUIRE((numbers.size() == mod - 1) == is_generator);
    }
}