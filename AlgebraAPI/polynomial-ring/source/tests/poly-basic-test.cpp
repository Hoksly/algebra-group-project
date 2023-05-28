#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../poly-ring-math.h"
#include <gmpxx.h>

using namespace modular;

TEST_CASE("Testing")
{
    SUBCASE("Test addition 1")
    {
        Polynomial<mpz_class> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);
        p1.addNode(1, 2);

        Polynomial<mpz_class> p2(5);
        p2.addNode(1, 0);
        p2.addNode(2, 1);
        p2.addNode(4, 2);

        Polynomial<mpz_class> p3(5);
        p3.addNode(3, 0);
        p1.print();
        p2.print();
        p3.print();
        (p1 + p2).print();

        REQUIRE(p3 == (p1 + p2));
    }

    SUBCASE("Test addition 2")
    {
        Polynomial<mpz_class> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);

        Polynomial<mpz_class> p2(5);
        p2.addNode(1, 2);
        p2.addNode(4, 3);

        Polynomial<mpz_class> p3(5);
        p3.addNode(2, 0);
        p3.addNode(3, 1);
        p3.addNode(1, 2);
        p3.addNode(4, 3);

        REQUIRE(p3 == (p1 + p2));
    }

    SUBCASE("Test addition 3")
    {
        Polynomial<mpz_class> p1(7);
        p1.addNode(4, 0);
        p1.addNode(2, 1);
        p1.addNode(8, 2);
        p1.addNode(7, 3);

        Polynomial<mpz_class> p2(7);
        p2.addNode(0, 0);

        Polynomial<mpz_class> p3(7);
        p3.addNode(4, 0);
        p3.addNode(2, 1);
        p3.addNode(1, 2);
        Polynomial<mpz_class> p4 = p1 + p2;

        REQUIRE(p3 == (p1 + p2));
    }

    SUBCASE("Test subtraction 1")
    {
        Polynomial<mpz_class> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);
        p1.addNode(1, 2);

        Polynomial<mpz_class> p2(5);
        p2.addNode(1, 0);
        p2.addNode(2, 1);
        p2.addNode(4, 2);

        Polynomial<mpz_class> p3(5);
        p3.addNode(1, 0);
        p3.addNode(1, 1);
        p3.addNode(2, 2);

        REQUIRE(p3 == (p1 - p2));
    }

    SUBCASE("Test subtraction 2")
    {
        Polynomial<mpz_class> p1(5);
        p1.addNode(3, 0);
        p1.addNode(5, 1);
        p1.addNode(8, 2);
        p1.addNode(12, 3);

        Polynomial<mpz_class> p2(5);
        p2.addNode(0, 0);

        Polynomial<mpz_class> p3(5);
        p3.addNode(3, 0);
        p3.addNode(3, 2);
        p3.addNode(2, 3);

        REQUIRE(p3 == (p1 - p2));
    }

    SUBCASE("Test subtraction 3")
    {
        Polynomial<mpz_class> p1(2);
        p1.addNode(3, 0);
        p1.addNode(7, 1);
        p1.addNode(6, 2);
        p1.addNode(9, 3);

        Polynomial<mpz_class> p2(2);
        p2.addNode(4, 0);
        p2.addNode(3, 1);
        p2.addNode(5, 2);

        Polynomial<mpz_class> p3(2);
        p3.addNode(1, 0);
        p3.addNode(1, 2);
        p3.addNode(1, 3);

        REQUIRE(p3 == (p1 - p2));
    }

    SUBCASE("Test multiplication 1")
    {
        Polynomial<mpz_class> p1(5);
        p1.addNode(3, 5);
        p1.addNode(7, 3);
        p1.addNode(2, 1);

        Polynomial<mpz_class> p2(5);
        p2.addNode(4, 4);
        p2.addNode(2, 3);
        p2.addNode(6, 1);

        Polynomial<mpz_class> p3(5);
        p3.addNode(2, 9);
        p3.addNode(1, 8);
        p3.addNode(3, 7);
        p3.addNode(2, 6);
        p3.addNode(3, 5);
        p3.addNode(1, 4);
        p3.addNode(2, 2);

        REQUIRE(p3 == (p1 * p2));
    }

    SUBCASE("Test multiplication 2")
    {
        Polynomial<mpz_class> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);
        p1.addNode(1, 2);

        Polynomial<mpz_class> p2(5);
        p2.addNode(1, 0);
        p2.addNode(2, 1);
        p2.addNode(4, 2);

        Polynomial<mpz_class> p3(5);
        p3.addNode(2, 0);
        p3.addNode(2, 1);
        p3.addNode(4, 3);
        p3.addNode(4, 4);

        REQUIRE(p3 == (p1 * p2));
    }

    SUBCASE("Test multiplication 3")
    {
        Polynomial<mpz_class> p1(2);
        p1.addNode(1, 0);
        p1.addNode(1, 1);

        Polynomial<mpz_class> p2(2);
        p2.addNode(1, 0);
        p2.addNode(1, 1);

        Polynomial<mpz_class> p3(2);
        p3.addNode(1, 0);
        p3.addNode(1, 2);

        REQUIRE(p3 == (p1 * p2));
    }

    SUBCASE("Test multiplication 4")
    {
        Polynomial<mpz_class> p1(2);
        p1.addNode(1, 0);
        p1.addNode(3, 1);
        p1.addNode(2, 3);

        Polynomial<mpz_class> p2(2);
        p2.addNode(0, 0);

        Polynomial<mpz_class> p3(2);
        p3.addNode(0, 0);

        REQUIRE(p3 == (p1 * p2));
    }
}
TEST_CASE("Testing division, gcd")
{
    SUBCASE("Test 0 - remainder")
    {
        Polynomial<mpz_class> p1(7);
        p1.addNode(1, 2);
        p1.addNode(1, 1);
        p1.addNode(1, 0);

        Polynomial<mpz_class> p2(7);
        p2.addNode(2, 1);
        p2.addNode(2, 0);

        // p1.print();
        // p2.print();

        Polynomial<mpz_class> res = p1 % p2;

        // res.print();

        Polynomial<mpz_class> expected(2);
        expected.addNode(1, 0);

        REQUIRE(res == expected);
    }

    SUBCASE("Test 1")
    {
        Polynomial<mpz_class> p1(37);
        p1.addNode(2, 4);
        p1.addNode(27, 3);
        p1.addNode(36, 2);
        p1.addNode(10, 1);
        p1.addNode(27, 0);

        Polynomial<mpz_class> p2(37);
        p2.addNode(2, 1);
        p2.addNode(3, 0);

        std::pair<Polynomial<mpz_class>, Polynomial<mpz_class>> res = p1.divClassic(p2);

        Polynomial<mpz_class> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);
    }

    SUBCASE("Test 2")
    {
        Polynomial<mpz_class> p1(5);
        p1.addNode(3, 4);
        p1.addNode(1, 3);
        p1.addNode(2, 2);
        p1.addNode(1, 0);

        Polynomial<mpz_class> p2(5);
        p2.addNode(1, 2);
        p2.addNode(4, 1);
        p2.addNode(2, 0);

        std::pair<Polynomial<mpz_class>, Polynomial<mpz_class>> res = p1.divClassic(p2);
        Polynomial<mpz_class> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);
    }

    SUBCASE("Test 3 - divisor - constant")
    {
        Polynomial<mpz_class> p1(37);
        p1.addNode(6, 4);
        p1.addNode(27, 3);
        p1.addNode(36, 2);
        p1.addNode(9, 1);
        p1.addNode(27, 0);

        Polynomial<mpz_class> p2(37);
        p2.addNode(3, 0);

        std::pair<Polynomial<mpz_class>, Polynomial<mpz_class>> res = p1.divClassic(p2);

        Polynomial<mpz_class> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);
    }

    SUBCASE("Test 4 - p2 empty")
    {
        Polynomial<mpz_class> p1(37);
        p1.addNode(6, 4);
        p1.addNode(27, 3);
        p1.addNode(36, 2);
        p1.addNode(9, 1);
        p1.addNode(27, 0);

        Polynomial<mpz_class> p2(37);

        CHECK_THROWS_WITH(p1 / p2, "Divisor must have at least one non-zero coefficient");
    }

    SUBCASE("Test 5 - numerator degree < divisor degree")
    {
        Polynomial<mpz_class> p1(11);
        p1.addNode(6, 3);
        p1.addNode(8, 2);
        p1.addNode(10, 1);
        p1.addNode(1, 0);

        Polynomial<mpz_class> p2(11);
        p2.addNode(7, 7);

        std::pair<Polynomial<mpz_class>, Polynomial<mpz_class>> res = p1.divClassic(p2);

        Polynomial<mpz_class> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);

        // CHECK_THROWS_WITH(p2 / p1, "The degree of the divisor cannot exceed that of the numerator");
    }

    SUBCASE("Test 6 - gcd")
    {
        Polynomial<mpz_class> p1(2);
        p1.addNode(1, 2);
        p1.addNode(1, 0);

        Polynomial<mpz_class> p2(2);
        p2.addNode(1, 1);
        p2.addNode(1, 0);

        auto gcd = p1.gcd(p2);

        Polynomial<mpz_class> expected(2);
        expected.addNode(1, 1);
        expected.addNode(1, 0);

        REQUIRE(gcd == expected);
    }

    SUBCASE("Test 7 - gcd")
    {
        Polynomial<mpz_class> p1(5);
        p1.addNode(2, 4);
        p1.addNode(3, 3);
        p1.addNode(3, 1);
        p1.addNode(3, 0);

        Polynomial<mpz_class> p2(5);
        p2.addNode(1, 3);
        p2.addNode(4, 1);
        p2.addNode(1, 0);

        auto gcd = p1.gcd(p2);
        Polynomial<mpz_class> expected(5);
        expected.addNode(1, 1);
        expected.addNode(2, 0);

        REQUIRE(gcd == expected);
    }

    SUBCASE("Test 8 - gcd")
    {
        Polynomial<mpz_class> p1(7);
        p1.addNode(3, 4);
        p1.addNode(6, 3);
        p1.addNode(3, 2);
        p1.addNode(2, 1);
        p1.addNode(3, 0);

        Polynomial<mpz_class> p2(7);
        p2.addNode(2, 3);
        p2.addNode(5, 1);
        p2.addNode(1, 0);

        auto gcd = p1.gcd(p2);
        Polynomial<mpz_class> expected(5);
        expected.addNode(1, 1);
        expected.addNode(4, 0);

        REQUIRE(gcd == expected);
    }

    SUBCASE("Test 9 - gcd")
    {
        Polynomial<mpz_class> p1(3);
        p1.addNode(1, 4);
        p1.addNode(2, 3);
        p1.addNode(2, 1);
        p1.addNode(1, 0);

        Polynomial<mpz_class> p2(3);
        p2.addNode(1, 3);
        p2.addNode(2, 2);
        p2.addNode(1, 0);

        auto gcd = p1.gcd(p2);

        Polynomial<mpz_class> expected(3);
        expected.addNode(1, 0);

        REQUIRE(gcd == expected);
    }
    SUBCASE("Test 10 - gcd")
    {
        Polynomial<mpz_class> p1(7);
        p1.addNode(3, 6);
        p1.addNode(2, 2);
        p1.addNode(1, 1);
        p1.addNode(5, 0);

        Polynomial<mpz_class> p2(7);
        p2.addNode(6, 4);
        p2.addNode(1, 3);
        p2.addNode(2, 1);
        p2.addNode(4, 0);

        auto gcd = p1.gcd(p2);

        Polynomial<mpz_class> expected(7);
        expected.addNode(1, 0);

        REQUIRE(gcd == expected);
    }

    SUBCASE("Test 11 - remainder")
    {
        Polynomial<mpz_class> p1(3);
        p1.addNode(1, 80);
        p1.addNode(-1, 0);

        Polynomial<mpz_class> p2(3);
        p2.addNode(1, 4);
        p2.addNode(1, 1);
        p2.addNode(2, 0);

        Polynomial<mpz_class> res = p1 % p2;

        Polynomial<mpz_class> expected(3);
        expected.addNode(0, 0);

        REQUIRE(res == expected);
    }
}

TEST_CASE("New constructor")
{
    std::vector<std::pair<int, size_t>> p1 = {{3, 3}, {4, 2}, {5, 1}, {6, 0}};
    std::vector<std::pair<int, size_t>> p2 = {{4, 4}};

    Polynomial<int> poly1(p1, 11);
    Polynomial<int> poly2(p2, 11);

    Polynomial<int> poly3 = poly1 + poly2;
    Polynomial<int> poly3_test();

    poly3.print();
}