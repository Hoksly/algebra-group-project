#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <gmpxx.h>

#include <iostream>
#include <vector>

#include "../../poly-ring-math.h"
#include "../../../doctest.h"

// int
// main() {
//     Polynomial<mpz_class> p1;
//     p1.fromCyclotomic(26, 73);
//     p1.print();
//     // auto v = getCyclotomicPolynomialRaw(12);
//     // cout << v;
//     return 0;
// }

TEST_CASE("Cyclotomic Polynomial Test") {
    DOCTEST_SUBCASE("Prime N") {
        std::vector<int32_t> result = getCyclotomicPolynomialRaw<int32_t>(17);
        std::vector<int32_t> expected = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        CHECK(result == expected);
    }

    DOCTEST_SUBCASE("Cyclotomic Polynomial test, Polynomial class") {
        Polynomial<int32_t> p;
        p.fromCyclotomic(4, 4);

        p.print();
    }

    DOCTEST_SUBCASE("Cyclotomic Polynomial test, Polynomial + MPZ class") {
        Polynomial<mpz_class> p;
        p.fromCyclotomic(5, 1);
        p.print();

        p.fromCyclotomic(10, 1);
        p.print();

        p.fromCyclotomic(11, 1);
        p.print();

        p.fromCyclotomic(25, 1);
        p.print();
    }

    DOCTEST_SUBCASE("Small values") {
        // N = 1
        std::vector<int32_t> result = getCyclotomicPolynomialRaw<int32_t>(1);
        CHECK_EQ(result, std::vector<int32_t>({1, -1}));

        // N = 2
        result = getCyclotomicPolynomialRaw<int32_t>(2);
        CHECK_EQ(result, std::vector<int32_t>({1, 1}));

        // N = 3
        result = getCyclotomicPolynomialRaw<int32_t>(3);
        CHECK_EQ(result, std::vector<int32_t>({1, 1, 1}));

        // N = 4
        result = getCyclotomicPolynomialRaw<int32_t>(4);
        CHECK_EQ(result, std::vector<int32_t>({1, 0, 1}));

        // N = 5
        result = getCyclotomicPolynomialRaw<int32_t>(5);
        CHECK_EQ(result, std::vector<int32_t>({1, 1, 1, 1, 1}));

        // N = 6
        result = getCyclotomicPolynomialRaw<int32_t>(6);
        CHECK_EQ(result, std::vector<int32_t>({1, -1, 1}));
    }

    DOCTEST_SUBCASE("Cyclotomic Polynomial test, large values") {
        // N = 10
        std::vector<int32_t> result = getCyclotomicPolynomialRaw<int32_t>(10);
        CHECK_EQ(result, std::vector<int32_t>({1, -1, 1, -1, 1}));

        // N = 15
        result = getCyclotomicPolynomialRaw<int32_t>(15);
        CHECK_EQ(result, std::vector<int32_t>({1, -1, 0, 1, -1, 1, 0, -1, 1}));

        // N = 20
        result = getCyclotomicPolynomialRaw<int32_t>(20);
        CHECK_EQ(result, std::vector<int32_t>({1, 0, -1, 0, 1, 0, -1, 0, 1}));

        // N = 25
        result = getCyclotomicPolynomialRaw<int32_t>(25);
        CHECK_EQ(result, std::vector<int32_t>({1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}));

        // N = 30
        result = getCyclotomicPolynomialRaw<int32_t>(30);
        CHECK_EQ(result, std::vector<int32_t>({1, 1, 0, -1, -1, -1, 0, 1, 1}));
    }
}
