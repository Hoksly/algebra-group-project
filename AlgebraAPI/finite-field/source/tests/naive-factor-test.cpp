#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../mod-math.h"
#include "utils.h"
#include <random>

using namespace modular;

TEST_CASE("Testing Naive factorization") {
    using T = long long;

    SUBCASE("Test1") {
        T mod = 16323010999;
        
        std::vector<modNum<T>> nf0 = naiveFactorize(modNum<T>(4853343967, mod));
        std::vector<modNum<T>> factors0{modNum<T>(55817, mod), modNum<T>(86951, mod)};
        sort(nf0.begin(), nf0.end());
        REQUIRE(nf0 == factors0);

        std::vector<modNum<T>> nf1 = naiveFactorize(modNum<T>(10403, mod));
        std::vector<modNum<T>> factors1{modNum<T>(101, mod), modNum<T>(103, mod)};
        sort(nf1.begin(), nf1.end());
        REQUIRE(nf1 == factors1);

        std::vector<modNum<T>> nf2 = naiveFactorize(modNum<T>(121, mod));
        std::vector<modNum<T>> factors2{modNum<T>(11, mod), modNum<T>(11, mod)};
        REQUIRE(nf2 == factors2);

        std::vector<modNum<T>> nf3 = naiveFactorize(modNum<T>(433, mod));
        std::vector<modNum<T>> factors3{modNum<T>(433, mod)};
        REQUIRE(nf3 == factors3);

        std::vector<modNum<T>> nf4 = naiveFactorize(modNum<T>(1232, mod+1));
        sort(nf4.begin(), nf4.end());
        std::vector<modNum<T>> factors4{modNum<T>(2, mod+1), modNum<T>(2, mod+1), modNum<T>(2, mod+1),
                                        modNum<T>(2, mod+1), modNum<T>(7, mod+1), modNum<T>(11, mod+1)};
        REQUIRE(nf4 == factors4);

        std::vector<modNum<T>> nf5 = naiveFactorize(modNum<T>(4853343968, mod));
        std::vector<modNum<T>> factors5{modNum<T>(2, mod),modNum<T>(2, mod),modNum<T>(2, mod),
        modNum<T>(2, mod),modNum<T>(2, mod),modNum<T>(11, mod), modNum<T>(13787909, mod)};
        sort(nf5.begin(), nf5.end());
        REQUIRE(nf5 == factors5);
    }

    SUBCASE("Test2") {
        for (long long i = 2; i <= 100000; ++i) {
            bool isExceptionThrown = false;
            try {
                std::vector<modNum<T>> num1 = naiveFactorize(modNum<T>(i, i+1));

            } catch (std::exception &e) {
                isExceptionThrown = true;
            }
            REQUIRE(!isExceptionThrown);
        }
    }

    SUBCASE("Test3") {
        T mod = getRandomNumber(1, getRandomNumber(1, 100000));
        modNum<T> a(getRandomNumber(1, getRandomNumber(1, 100000)), mod);

        std::vector<modNum<T>> f1 = naiveFactorize(a);

        modNum<T> mult (1,mod);
        bool isExceptionThrown = false;
        for (auto numb : f1) {
            if (!isPrimeSimple(numb.getValue()))
                break;
            mult = mult * numb;
        }

        REQUIRE(a == mult);
    }
}