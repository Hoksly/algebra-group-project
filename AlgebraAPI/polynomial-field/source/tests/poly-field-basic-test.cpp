#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../poly-field-math.h"

TEST_CASE("Test addition 1") {
    std::vector<std::pair<int, size_t>> arrrr = {{3, 3}, {4, 2}, {5, 1}, {6, 0}};
    std::vector<std::pair<int, size_t>> mod = {{7, 7}};

    PolynomialField<int> pol1(11, mod, arrrr);

    std::vector<std::pair<int, size_t>> arrrr2 = {{3, 3}, {4, 2}, {5, 1}, {6, 0}};

    PolynomialField<int> pol2(11, mod, arrrr2);

    PolynomialField<int> pol3 = pol1 + pol2;

    pol3.print();

    std::vector<std::pair<int, size_t>> arrrr3 = {{6, 3}, {8, 2}, {10, 1}, {1, 0}};

    PolynomialField<int> pol4(11, mod, arrrr3);

    REQUIRE(pol3 == pol4);
}
TEST_CASE("Test subtraction 1") {
    std::vector<std::pair<int, size_t>> arrrr = {{2, 4}, {5, 3}, {3, 2}, {3, 1}, {1, 0}};
    std::vector<std::pair<int, size_t>> mod = {{1, 2}};

    PolynomialField<int> pol1(7, mod, arrrr);

    std::vector<std::pair<int, size_t>> arrrr2 = {{3, 3}, {1, 2}, {1, 1}, {1, 0}};

    PolynomialField<int> pol2(7, mod, arrrr2);

    PolynomialField<int> pol3 = pol1 - pol2;

    pol3.print();

    std::vector<std::pair<int, size_t>> arrrr3 = {{2, 1}};

    PolynomialField<int> pol4(7, mod, arrrr3);

    REQUIRE(pol3 == pol4);
}

TEST_CASE("Test multiplication") {
    std::vector<std::pair<int, size_t>> arrrr = {{3, 2}, {2, 1}, {1, 0}};
    std::vector<std::pair<int, size_t>> mod = {{1, 1}, {1, 0}};

    PolynomialField<int> pol1(7, mod, arrrr);

    std::vector<std::pair<int, size_t>> arrrr2 = {{3, 2}, {2, 1}, {1, 0}};

    PolynomialField<int> pol2(7, mod, arrrr2);

    PolynomialField<int> pol3 = pol1 * pol2;

    pol3.print();

    std::vector<std::pair<int, size_t>> arrrr3 = {{-3, 0}};

    PolynomialField<int> pol4(7, mod, arrrr3);

    REQUIRE(pol3 == pol4);
}

TEST_CASE("Test pow") {
    std::vector<std::pair<int, size_t>> arrrr = {{3, 2}, {2, 1}, {1, 0}};
    std::vector<std::pair<int, size_t>> mod = {{1, 1}, {1, 0}};

    PolynomialField<int> pol1(7, mod, arrrr);

    PolynomialField<int> pol3 = pol1.pow(2);

    pol3.print();

    std::vector<std::pair<int, size_t>> arrrr3 = {{-3, 0}};

    PolynomialField<int> pol4(7, mod, arrrr3);

    REQUIRE(pol3 == pol4);
}