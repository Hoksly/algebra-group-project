// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

// #include "../../../doctest.h"
// #include "../../mod-math.h"
// #include <random>
// #include "utils.h"

// TEST_CASE("Naive tests")
// {
//     int num = 7;
//     int mod = 31;

//     int order = orderOfElement(modNum<int>(num, mod));

//     CHECK(fpow(modNum<int>(num, mod), order).getValue() == 1);

//     num = 9;
//     order = orderOfElement(modNum<int>(num, mod));
// }

// TEST_CASE("Random tests")
// {
//     for (int i = 0; i < 1000; ++i)
//     {
//         int num = getRandomNumber(1, 10000);
//         int mod = getRandomNumber(10000, 20000);

//         int order = orderOfElement(modNum<int>(num, mod));

//         CHECK(fpow(modNum<int>(num, mod), order).getValue() == 1);
//     }
// }
