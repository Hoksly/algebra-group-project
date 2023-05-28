#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../mod-math.h"

#include "utils.h"
#include <random>
#include <time.h>
#include <chrono>
#include <gmpxx.h>

using namespace modular;

TEST_CASE("Testing Pollard factorization")
{
    using T = long long;
    using T2 = mpz_class;

    SUBCASE("Test1")
    {
        //  T mod = 8*1763668414462081;
        //     std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

        //     startTime = std::chrono::system_clock::now();
        //     std::vector<modNum<T>> nf0 = naiveFactorize(modNum<T>(7*1763668414462081, mod));
        //     endTime = std::chrono::system_clock::now();
        //     std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms" << std::endl;

        //     startTime = std::chrono::system_clock::now();
        //     std::vector<modNum<T>> pf0 = factorize(modNum<T>(7*1763668414462081, mod));
        //     endTime = std::chrono::system_clock::now();
        //     std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms" << std::endl;
        // }
        mpz_class numb1 = 46181;
        mpz_class numb2 = 31393;
        mpz_class numb = numb1 * numb2;
        mpz_class mod2 = numb * 2;

        std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

        startTime = std::chrono::system_clock::now();
        std::vector<modNum<T2>> nf10 = naiveFactorize(modNum<T2>(numb, mod2));
        endTime = std::chrono::system_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms" << std::endl;

        startTime = std::chrono::system_clock::now();
        std::vector<modNum<T2>> pf10 = factorize(modNum<T2>(numb, mod2));
        endTime = std::chrono::system_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms" << std::endl;

        sort(nf10.begin(), nf10.end());
        sort(pf10.begin(), pf10.end());
        REQUIRE(nf10 == pf10);

        T mod = 4853343968;

        std::vector<modNum<T>> pf0 = factorize(modNum<T>(4853343967, mod));
        std::vector<modNum<T>> factors0{modNum<T>(55817, mod), modNum<T>(86951, mod)};
        sort(pf0.begin(), pf0.end());
        REQUIRE(pf0 == factors0);

        std::vector<modNum<T>> pf1 = factorize(modNum<T>(10403, mod));
        std::vector<modNum<T>> factors1{modNum<T>(101, mod), modNum<T>(103, mod)};
        sort(pf1.begin(), pf1.end());
        REQUIRE(pf1 == factors1);

        std::vector<modNum<T>> pf2 = factorize(modNum<T>(121, mod));
        std::vector<modNum<T>> factors2{modNum<T>(11, mod), modNum<T>(11, mod)};
        REQUIRE(pf2 == factors2);

        std::vector<modNum<T>> pf3 = factorize(modNum<T>(433, mod));
        std::vector<modNum<T>> factors3{modNum<T>(433, mod)};
        REQUIRE(pf3 == factors3);

        std::vector<modNum<T>> pf4 = factorize(modNum<T>(1232, mod + 1));
        sort(pf4.begin(), pf4.end());
        std::vector<modNum<T>> factors4{modNum<T>(2, mod + 1), modNum<T>(2, mod + 1), modNum<T>(2, mod + 1),
                                        modNum<T>(2, mod + 1), modNum<T>(7, mod + 1), modNum<T>(11, mod + 1)};
        REQUIRE(pf4 == factors4);
    }

    SUBCASE("Test2")
    {
        for (long long i = 2; i <= 10000; ++i)
        {
            bool isExceptionThrown = false;
            try
            {
                std::vector<modNum<T>> num1 = factorize(modNum<T>(i, i + 1));
            }
            catch (std::exception &e)
            {
                isExceptionThrown = true;
            }
            REQUIRE(!isExceptionThrown);
        }
    }

    SUBCASE("Test3")
    {
        T mod = getRandomNumber(1, getRandomNumber(1, 100000));
        modNum<T> a(getRandomNumber(1, getRandomNumber(100000, 200000)), mod);

        std::vector<modNum<T>> f1 = factorize(a);

        modNum<T> mult(1, mod);
        bool isExceptionThrown = false;
        for (auto numb : f1)
        {
            if (!isPrimeSimple(numb.getValue()))
                break;
            mult = mult * numb;
        }

        REQUIRE(a == mult);
    }
}