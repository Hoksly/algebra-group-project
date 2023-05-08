#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../poly-basic.tcc"
#include "../../../doctest.h"

using namespace modular;

TEST_CASE("Testing")
{
    SUBCASE("Test addition 1")
    {
        Polynomial<int> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);
        p1.addNode(1, 2);

        Polynomial<int> p2(5);
        p2.addNode(1, 0);
        p2.addNode(2, 1);
        p2.addNode(4, 2);

        Polynomial<int> p3(5);
        p3.addNode(3, 0);
        p1.print();
        p2.print();
        p3.print();
        (p1 + p2).print();

        REQUIRE(p3 == (p1 + p2));
    }

    SUBCASE("Test addition 2")
    {
        Polynomial<int> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);

        Polynomial<int> p2(5);
        p2.addNode(1, 2);
        p2.addNode(4, 3);

        Polynomial<int> p3(5);
        p3.addNode(2, 0);
        p3.addNode(3, 1);
        p3.addNode(1, 2);
        p3.addNode(4, 3);

        REQUIRE(p3 == (p1 + p2));
    }

    SUBCASE("Test addition 3")
    {
        Polynomial<int> p1(7);
        p1.addNode(4, 0);
        p1.addNode(2, 1);
        p1.addNode(8, 2);
        p1.addNode(7, 3);

        Polynomial<int> p2(7);
        p2.addNode(0, 0);

        Polynomial<int> p3(7);
        p3.addNode(4, 0);
        p3.addNode(2, 1);
        p3.addNode(1, 2);
        Polynomial<int> p4 = p1 + p2;

        REQUIRE(p3 == (p1 + p2));
    }

    SUBCASE("Test subtraction 1")
    {
        Polynomial<int> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);
        p1.addNode(1, 2);

        Polynomial<int> p2(5);
        p2.addNode(1, 0);
        p2.addNode(2, 1);
        p2.addNode(4, 2);

        Polynomial<int> p3(5);
        p3.addNode(1, 0);
        p3.addNode(1, 1);
        p3.addNode(2, 2);

        REQUIRE(p3 == (p1 - p2));
    }

    SUBCASE("Test subtraction 2")
    {
        Polynomial<int> p1(5);
        p1.addNode(3, 0);
        p1.addNode(5, 1);
        p1.addNode(8, 2);
        p1.addNode(12, 3);

        Polynomial<int> p2(5);
        p2.addNode(0, 0);

        Polynomial<int> p3(5);
        p3.addNode(3, 0);
        p3.addNode(3, 2);
        p3.addNode(2, 3);

        REQUIRE(p3 == (p1 - p2));
    }

    SUBCASE("Test subtraction 3")
    {
        Polynomial<int> p1(2);
        p1.addNode(3, 0);
        p1.addNode(7, 1);
        p1.addNode(6, 2);
        p1.addNode(9, 3);

        Polynomial<int> p2(2);
        p2.addNode(4, 0);
        p2.addNode(3, 1);
        p2.addNode(5, 2);

        Polynomial<int> p3(2);
        p3.addNode(1, 0);
        p3.addNode(1, 2);
        p3.addNode(1, 3);

        REQUIRE(p3 == (p1 - p2));
    }

    SUBCASE("Test multiplication 1")
    {
        Polynomial<int> p1(5);
        p1.addNode(3, 5);
        p1.addNode(7, 3);
        p1.addNode(2, 1);

        Polynomial<int> p2(5);
        p2.addNode(4, 4);
        p2.addNode(2, 3);
        p2.addNode(6, 1);

        Polynomial<int> p3(5);
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
        Polynomial<int> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);
        p1.addNode(1, 2);

        Polynomial<int> p2(5);
        p2.addNode(1, 0);
        p2.addNode(2, 1);
        p2.addNode(4, 2);

        Polynomial<int> p3(5);
        p3.addNode(2, 0);
        p3.addNode(2, 1);
        p3.addNode(4, 3);
        p3.addNode(4, 4);

        REQUIRE(p3 == (p1 * p2));
    }

    SUBCASE("Test multiplication 3")
    {
        Polynomial<int> p1(2);
        p1.addNode(1, 0);
        p1.addNode(1, 1);

        Polynomial<int> p2(2);
        p2.addNode(1, 0);
        p2.addNode(1, 1);

        Polynomial<int> p3(2);
        p3.addNode(1, 0);
        p3.addNode(1, 2);

        REQUIRE(p3 == (p1 * p2));
    }

    SUBCASE("Test multiplication 4")
    {
        Polynomial<int> p1(2);
        p1.addNode(1, 0);
        p1.addNode(3, 1);
        p1.addNode(2, 3);

        Polynomial<int> p2(2);
        p2.addNode(0, 0);

        Polynomial<int> p3(2);
        p3.addNode(0, 0);

        REQUIRE(p3 == (p1 * p2));
    }
}
TEST_CASE("Testing division, gcd")
{
    SUBCASE("Test 1")
    {
        Polynomial<int> p1(37);
        p1.addNode(2, 4);
        p1.addNode(27, 3);
        p1.addNode(36, 2);
        p1.addNode(10, 1);
        p1.addNode(27, 0);

        Polynomial<int> p2(37);
        p2.addNode(2, 1);
        p2.addNode(3, 0);

        std::pair<Polynomial<int>, Polynomial<int>> res = p1 / p2;

        Polynomial<int> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);
    }

    SUBCASE("Test 2")
    {
        Polynomial<int> p1(5);
        p1.addNode(3, 4);
        p1.addNode(1, 3);
        p1.addNode(2, 2);
        p1.addNode(1, 0);

        Polynomial<int> p2(5);
        p2.addNode(1, 2);
        p2.addNode(4, 1);
        p2.addNode(2, 0);

        std::pair<Polynomial<int>, Polynomial<int>> res = p1 / p2;
        Polynomial<int> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);
    }

    SUBCASE("Test 3 - divisor - constant")
    {
        Polynomial<int> p1(40);
        p1.addNode(6, 4);
        p1.addNode(27, 3);
        p1.addNode(36, 2);
        p1.addNode(9, 1);
        p1.addNode(27, 0);

        Polynomial<int> p2(40);
        p2.addNode(3, 0);

        std::pair<Polynomial<int>, Polynomial<int>> res = p1 / p2;

        Polynomial<int> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);
    }

    SUBCASE("Test 4 - p2 empty")
    {
        Polynomial<int> p1(40);
        p1.addNode(6, 4);
        p1.addNode(27, 3);
        p1.addNode(36, 2);
        p1.addNode(9, 1);
        p1.addNode(27, 0);

        Polynomial<int> p2(40);

        CHECK_THROWS_WITH(p1 / p2, "Divisor must have at least one non-zero coefficient");
    }

    SUBCASE("Test 5 - numerator degree < divisor degree")
    {
        Polynomial<int> p1(40);
        p1.addNode(2, 4);
        p1.addNode(27, 3);
        p1.addNode(36, 2);
        p1.addNode(10, 1);
        p1.addNode(27, 0);

        Polynomial<int> p2(40);
        p2.addNode(2, 1);
        p2.addNode(3, 0);

        CHECK_THROWS_WITH(p2 / p1, "The degree of the divisor cannot exceed that of the numerator");
    }

    SUBCASE("Test 6 - gcd")
    {
        Polynomial<int> p1(2);
        p1.addNode(1, 2);
        p1.addNode(1, 0);

        Polynomial<int> p2(2);
        p2.addNode(1, 1);
        p2.addNode(1, 0);

        auto gcd = p1.gcd(p2);

        Polynomial<int> expected(2);
        expected.addNode(1, 1);
        expected.addNode(1, 0);

        REQUIRE(gcd == expected);
    }

    SUBCASE("Test 7 - gcd")
    {
        Polynomial<int> p1(5);
        p1.addNode(2, 4);
        p1.addNode(3, 3);
        p1.addNode(3, 1);
        p1.addNode(3, 0);

        Polynomial<int> p2(5);
        p2.addNode(1, 3);
        p2.addNode(4, 1);
        p2.addNode(1, 0);

        auto gcd = p1.gcd(p2);
        Polynomial<int> expected(5);
        expected.addNode(1, 1);
        expected.addNode(2, 0);

        REQUIRE(gcd == expected);
    }

    SUBCASE("Test 8 - gcd")
    {
        Polynomial<int> p1(7);
        p1.addNode(3, 4);
        p1.addNode(6, 3);
        p1.addNode(3, 2);
        p1.addNode(2, 1);
        p1.addNode(3, 0);

        Polynomial<int> p2(7);
        p2.addNode(2, 3);
        p2.addNode(5, 1);
        p2.addNode(1, 0);

        auto gcd = p1.gcd(p2);
        Polynomial<int> expected(5);
        expected.addNode(1, 1);
        expected.addNode(4, 0);

        REQUIRE(gcd == expected);
    }

    SUBCASE("Test 9 - gcd")
    {
        Polynomial<int> p1(3);
        p1.addNode(1,4);
        p1.addNode(2,3);
        p1.addNode(2,1);
        p1.addNode(1,0);


        Polynomial<int> p2(3);
        p2.addNode(1,3);
        p2.addNode(2,2);
        p2.addNode(1,0);

        auto gcd = p1.gcd(p2);

        Polynomial<int> expected(3);
        expected.addNode(1,0);

        REQUIRE(gcd == expected);
    }
    SUBCASE("Test 10 - gcd")
    {
        Polynomial<int> p1(7);
        p1.addNode(3,6);
        p1.addNode(2,2);
        p1.addNode(1,1);
        p1.addNode(5,0);


        Polynomial<int> p2(7);
        p2.addNode(6,4);
        p2.addNode(1,3);
        p2.addNode(2,1);
        p2.addNode(4,0);

        auto gcd = p1.gcd(p2);

        Polynomial<int> expected(7);
        expected.addNode(1,0);

        REQUIRE(gcd == expected);
    }
}