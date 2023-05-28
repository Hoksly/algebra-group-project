#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../../doctest.h"
#include "../../mod-math.h"

#include <random>
#include "utils.h"
#include <gmpxx.h>

using namespace modular;
template <class T>

bool SimpleIsPrime(T n)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

TEST_CASE("Long arithmetic")
{
    mpz_class number;
    mpz_class mod;

    SUBCASE("First test")
    {
        number.set_str("1311790816646986218444823", 10);
        mod.set_str("627917618844137493480783674921", 10);
        CHECK_EQ(isPrime(modNum<mpz_class>(number, mod), 1000), true);
    }
    SUBCASE("Second test")
    {
        number.set_str("7146417642259700629173359", 10);
        mod.set_str("84768435013152452201149402649", 10);
        CHECK_EQ(isPrime(modNum<mpz_class>(number, mod), 1000), true);
    }
    SUBCASE("Third test")
    {
        number.set_str("13768210448371104944788065647947", 10);
        mod.set_str("9815244056604946342372848161758858649", 10);
        CHECK_EQ(isPrime(modNum<mpz_class>(number, mod), 1000), true);
    }
    SUBCASE("Fourth test")
    {
        number.set_str("8365464743131628640330841895509", 10);
        mod.set_str("2659476140164879773109669847065984141", 10);
        CHECK_EQ(isPrime(modNum<mpz_class>(number, mod), 1000), false);
    }
}

TEST_CASE("Testing the Miller-Rabin method to check a number for prime ")
{
    using T = long long;
    T mod = 16323010999;
    SUBCASE("Edge case")
    {
        CHECK_EQ(isPrime(modNum<T>(-1, mod), 100), SimpleIsPrime(1));
        CHECK_EQ(isPrime(modNum<T>(1, mod), 100), SimpleIsPrime(1));
        CHECK_EQ(isPrime(modNum<T>(2, mod), 100), SimpleIsPrime(2));
    }

    SUBCASE("Input from the console")
    {
        std::cout << "Enter the numbers you want to check for prime " << std::endl;
        T value;
        std::cin >> value;
        std::cout << "Enter the number of iterations that will set the verification accuracy"
                  << std::endl;
        int k;
        std::cin >> k;
        CHECK_EQ(isPrime(modNum<T>(value, mod), k), SimpleIsPrime(value));
        if (isPrime(modNum<T>(value, mod), k))
            std::cout << "Your number is prime" << std::endl;
        else
            std::cout << "Your number is NOT prime" << std::endl;
    }

    SUBCASE("Random values")
    {
        int num_errors = 0;
        for (int i = 0; i < 100000; ++i)
        {
            int value = getRandomNumber(1, 100000);
            int k = getRandomNumber(100, 1000);
            CHECK_EQ(isPrime(modNum<T>(value, mod), k), SimpleIsPrime(value));
        }
    }

    SUBCASE("Input from the file")
    {
        std::fstream input;
        T value;
        int k;

        input.open(
            "C:\\Users\\User\\Desktop\\PI-23\\Sem 2\\General "
            "Algebra\\algebra-group-project-vsc\\files\\input.txt");
        if (input.is_open())
        {
            input >> value >> k;
        }
        else
        {
            std::cout << "File isn't open" << std::endl;
        }

        CHECK_EQ(isPrime(modNum<T>(value, mod), k), SimpleIsPrime(value));

        std::ofstream outfile(
            "C:\\Users\\User\\Desktop\\PI-23\\Sem 2\\General "
            "Algebra\\algebra-group-project-vsc\\files\\output.txt");
        if (outfile.is_open())
        {
            if (isPrime(modNum<T>(value, mod), k))
                outfile << "Your number is prime" << std::endl;
            else
                outfile << "Your number is NOT prime" << std::endl;

            outfile.close();
        }
        input.close();
    }
}