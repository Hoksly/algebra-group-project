#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../poly-basic.tcc"
#include "../../../doctest.h"

using namespace modular;

TEST_CASE("Testing")
{
    SUBCASE("Test addition")
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

        REQUIRE(p3 == (p1 + p2));
    }

    SUBCASE("Test subtraction")
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

    SUBCASE("Test multiplication1")
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

    SUBCASE("Test multiplication2")
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
        p3.addNode(0, 2);
        p3.addNode(4, 3);
        p3.addNode(4, 4);

        REQUIRE(p3 == (p1 * p2));
    }
}