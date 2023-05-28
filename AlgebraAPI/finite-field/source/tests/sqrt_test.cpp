#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../mod-math.h"

TEST_CASE("Testing square root") {
    SUBCASE("Test 1") {
        modNum<int> num(9, 13);
        std::vector<int> test = modular::sqrt(num);
        std::vector<int> result = {3, 10};

        REQUIRE(test == result);
    }

    SUBCASE("Test 2") {
        modNum<int> num(15, 11);
        std::vector<int> test = modular::sqrt(num);
        std::vector<int> result = {2, 9};

        REQUIRE(test == result);
    }

    SUBCASE("Test 3") {
        modNum<int> num(26, 17);
        std::vector<int> test = modular::sqrt(num);
        std::vector<int> result = {3, 14};

        REQUIRE(test == result);
    }

    SUBCASE("Test 4") {
        modNum<int> num(34, 15);
        std::vector<int> test = modular::sqrt(num);
        std::vector<int> result = {7, 8, 2, 13};

        REQUIRE(test == result);
    }

    SUBCASE("Test 5") {
        modNum<int> num(58, 22);
        std::vector<int> test = modular::sqrt(num);
        std::vector<int> result = {6, 16};

        REQUIRE(test == result);
    }
}