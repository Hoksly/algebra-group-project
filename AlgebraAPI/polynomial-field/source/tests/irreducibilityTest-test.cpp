#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../poly-field-math.h"
#include "../../../polynomial-ring/poly-ring-math.h"
#include "../../../finite-field/mod-math.h"
#include <gmpxx.h>

using namespace modular;

TEST_CASE("IRREDUCIBILITY_TEST")
{
    Polynomial<long long> poly(static_cast<long long>(898181));
    Node<long long> one(modNum<long long>(1, 898181), 2);
    Node<long long> two(modNum<long long>(5, 898181), 1);
    Node<long long> three(modNum<long long>(10, 898181), 0);

    poly.addNode(one);
    poly.addNode(two);
    poly.addNode(three);
    CHECK_EQ(irreducibilityTest<long long>(poly), false);
}