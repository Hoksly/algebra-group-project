#ifndef FACTOR
#define FACTOR

#include <cassert>
#include <iostream>
#include <string>

#include "../mod-math.h"

using namespace std;
using namespace modular;

/**
 *  @brief Calculating GCD
 *  @param a first number
 *  @param b second number
 *  @return GCD
 */
template <typename T1, typename T2>
T2 gcd(T1 a, T2 b)
{
    return b == 0 ? a : gcd(b, a % b);
}

/**
 *  @brief Checks if the number is prime or not
 *  @param a first number
 *  @return true or false
 */
template <typename T1>
bool isPrimeSimple(T1 a)
{
    for (int i = 2; i <= sqrt(a); ++i)
        if (a % i == 0)
            return false;
    return true;
}

/**
 *  @brief Calculating a polynomial in x computed modulo mod
 *  @param x value
 *  @param mod modulo
 *  @return polynomial in x computed modulo mod
 */
template <typename T1>
T1 F(T1 x, T1 mod)
{
    T1 a = rand() % 10;
    return (x * x + (1 + 2 * a)) % mod;
}

/**
 *  @brief Pollard's rho algorithm
 *  @param n number
 *
 *
 *  @return factor
 */
template <typename T1>
T1 pollardRhO(T1 n)
{
    if (n % 2 == 0)
        return 2;

    T1 x = 2;
    T1 y = 2;
    T1 d = 1;

    while (d == 1)
    {
        x = F(x, n);
        y = F(F(y, n), n);
        d = gcd(abs(x - y), n);
    }
    return d;
}

/**
 *  @brief Factorization using Pollard's rho algorithm
 *  @param value number
 *  @return vector of factors
 */
template <typename T1>
template <typename T2>
std::vector<T2>
modNum<T1>::Pollard<T2>::factor(T2 value)
{
    if (value < 1)
        throw invalid_argument("value is less than 1");
    else if (value == 1)
        return vector<T2>{};
    else if (isPrime(modNum<T2>(value, value + 1), 10))
        return vector<T2>{value};

    vector<T2> factors;

    T2 divisor = pollardRhO(value);
    if (isPrime(modNum<T2>(value, value + 1), 10))
        factors.push_back(divisor);
    else
    {
        vector<T2> tmp = factor(divisor);
        factors.insert(factors.end(), tmp.begin(), tmp.end());
    }

    value = value / divisor;

    if (isPrime(modNum<T2>(value, value + 1), 10))
        factors.push_back(value);
    else
    {
        vector<T2> tmp = factor(value);
        factors.insert(factors.end(), tmp.begin(), tmp.end());
    }

    return factors;
}

/**
 *  @brief Factorization using naive algorithm
 *  @param value number
 *  @return vector of factors
 */
template <typename T1>
template <typename T2>
std::vector<T2>
modNum<T1>::Naive<T2>::factor(T2 m)
{
    if (m < 1)
        throw invalid_argument(" value is less than 1");
    else if (m == 1)
        return vector<T2>{};
    else if (isPrimeSimple(m))
        return vector<T2>{m};

    vector<T2> factors;

    T2 p = 2;
    while (p * p <= m)
    {
        if (m % p == 0)
        {
            m = m / p;
            factors.push_back(p);
        }
        else
        {
            p++;
        }
    }

    if (m > 1)
        factors.push_back(m);

    return factors;
}

// Adapter pattern
template <typename T1>
class Adapter : public modNum<T1>
{
    public:
    using modNum<T1>::modNum;

    std::vector<modNum<T1>> factorizeMod(typename modNum<T1>::template Factorization<T1> *strat)
    {
        this->setStrat(strat);

        std::vector<T1> factors = this->factorize();
    
        std::vector<modNum<T1>> res;
        T1 mod = this->getMod();
        for (int i = 0; i < factors.size(); i++)
            res.push_back(modNum<T1>(factors[i], mod));

        return res;
    }  
};


template <typename T1>
std::vector<modNum<T1>>
modular::factorize(modNum<T1> value) {
    typename modNum<T1>::template Naive<T1> strat;
    
    Adapter<T1> adapter(value.getValue(), value.getMod());
    std::vector<modNum<T1>> res = adapter.factorizeMod(&strat);

    return res;
}

template <typename T1>
std::vector<modNum<T1>>
modular::naiveFactorize(modNum<T1> value)   // number factorization using naive algorithm
{
    typename modNum<T1>::template Naive<T1> strat;
    Adapter<T1> adapter(value.getValue(), value.getMod());
    std::vector<modNum<T1>> res = adapter.factorizeMod(&strat);

    return res;
}
#endif