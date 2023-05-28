#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <random>

#include "../../../doctest.h"
#include "../inverse-poly.tcc"

using namespace modular;

TEST_CASE("Inverse polynomial")
{
    using T = int;
    SUBCASE("First test")
    {
        /*polyValue = Polinome("x^2+1"); polyMod = Polinome("x^3+2x+1"); result = Polinome("2x^2+x+2");*/
        T mod = 3;

        Polynomial<T> polyMod(mod);
        polyMod.addNode(1, 3);
        polyMod.addNode(2, 1);
        polyMod.addNode(1, 0);

        Polynomial<T> polyValue(mod);
        polyValue.addNode(1, 2);
        polyValue.addNode(1, 0);

        std::vector<std::pair<T, size_t>> res = {{2, 2}, {1, 1}, {2, 0}};
        Polynomial<T> result(res, mod);

        PolynomialField<T> polynomialfield(mod, polyMod, polyValue);

        REQUIRE(polynomialfield.inv().getValue() == result);
    }
    SUBCASE("Second test")
    {
        /*polyValue = Polinome("2x^2+2");  polyMod = Polinome("x^4+x^3+x^2+1"); result = Polinome("2x^3+x^2+2x+1");*/
        T mod = 3;

        Polynomial<T> polyMod(mod);
        polyMod.addNode(1, 4);
        polyMod.addNode(1, 3);
        polyMod.addNode(1, 2);
        polyMod.addNode(1, 0);

        Polynomial<T> polyValue(mod);
        polyValue.addNode(2, 2);
        polyValue.addNode(2, 0);

        std::vector<std::pair<T, size_t>> res = {{2, 3}, {1, 2}, {2, 1}, {1, 0}};
        Polynomial<T> result(res, mod);

        PolynomialField<T> polynomialfield(mod, polyMod, polyValue);

        REQUIRE(polynomialfield.inv().getValue() == result);
    }

    SUBCASE("Third test")
    {
        int mod = 17;
        Polynomial<T> polyMod(mod);
        polyMod.addNode(2, 4);
        polyMod.addNode(1, 3);
        polyMod.addNode(2, 2);
        polyMod.addNode(1, 0);

        Polynomial<T> polyValue(mod);
        polyValue.addNode(2, 2);
        polyValue.addNode(3, 0);

        PolynomialField<T> polynomialfield(mod, polyMod, polyValue);

        Polynomial<T> one(mod);
        one.addNode(1, 0);

        REQUIRE((polynomialfield.inv().getValue() * polyValue) % polyMod == one);
    }
}