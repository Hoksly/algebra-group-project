namespace modular
{

#ifndef ALGEBRA_INVERSION_AND_DIVISION
#define ALGEBRA_INVERSION_AND_DIVISION
#include <iostream>

#include "../mod-math.h"

    using namespace std;

    /**
    @file fpow.tcc
    @brief Implementation of Montgomery modular exponentiation algorithm
    */
    /**

    @brief Calculates the length of a number in a given base
    @tparam T1 Type of input number and base
    @param n Input number
    @param b Base
    @return Length of the number
    */
    template <typename T1>
    T1
    number_length(T1 n, T1 b)
    {
        int len = 0;
        while (n > 0)
        {
            n /= b;
            len++;
        }
        return len;
    }
    /**

    @brief Calculates k such that b^k > n
    @tparam T1 Type of input number and base
    @param n Input number
    @param b Base
    @return Value of k
    */
    template <typename T1>
    T1
    get_k(T1 n, T1 b)
    {
        T1 k = 0;
        while (b > 1 && b <= n)
        {
            b *= b;
            k++;
        }
        return k;
    }
    /**

    @brief Computes the resulting multiplier for Montgomery algorithm
    @tparam T1 Type of input number and base
    @param n Input number
    @return Value of t
    */
    template <typename T1>
    T1
    get_t(T1 n)
    {
        T1 t = 1;
        T1 two = 2;
        T1 k = number_length(n, two);
        for (int i = 0; i < k; i++)
        {
            t = (t * t) % n;
        }
        return t;
    }
    /**

    @brief Computes the modular exponentiation of a number using Montgomery algorithm

    @tparam T1 Type of input number and base

    @param value Base

    @param power Exponent

    @param n Modulus(get from class modNum)

    @return The result of a^b mod n
    */
    template <typename T1>
    modNum<T1>
    fpowdiif(modNum<T1> value, T1 power)
    {
        if (value == static_cast<T1>(0) && power == 0)
        {
            throw std::invalid_argument("0 pow 0 is undefined");
        }

        T1 n = value.getMod();
        T1 two = 2;
        T1 k = get_k(n, two);
        T1 r = 1;
        T1 t = get_t(n);

        return modNum<T1>((r * t) % n, value.getMod());
    }

    template <typename T>
    modNum<T>
    REDC(T num, T r, T MOD)
    {
        T n = modNum<T>(MOD, r).inv().getValue();
        T m = ((num % r) * n) % r;
        T res = (num - m * MOD) / r;
        res = (res < 0) ? res + MOD : res;
        return modNum<T>(res, MOD);
    }

    template <typename T>
    T logPow(T base, T power, T MOD)
    {
        T result = 1;
        while (power > 0)
        {
            if (power % 2 == 1)
            { // Can also use (power & 1) to make code even faster
                result = (result * base) % MOD;
            }
            base = (base * base) % MOD;
            power = power / 2; // Can also use power >>= 1; to make code even faster
        }
        return result;
    }

    template <typename T>
    modNum<T>
    fpowMontogomery(modNum<T> value, T power)
    {
        if (value == static_cast<T>(0) && power == 0)
        {
            throw std::invalid_argument("0 pow 0 is undefined");
        }
        T MOD = value.getMod();
        T r = 4096;
        while (r <= MOD)
            r = 2 * r;

        value = REDC(static_cast<T>(value.getValue() * ((r * r) % MOD)), r, MOD);
        modNum<T> result = modNum<T>(1, MOD);

        while (power > 0)
        {
            if (power % 2 == 1)
            { // Can also use (power & 1) to make code even faster
                result = result * value;
            }
            value = value * value;
            power = power / 2; // Can also use power >>= 1; to make code even faster
        }
        return REDC(static_cast<T>(result.getValue() * r % MOD), r, MOD);
    }

    template <typename T1>
    modNum<T1>
    classicLogPow(modNum<T1> value, T1 power)
    {
        modNum<T1> res = modNum<T1>(1, value.getMod());
        T1 two = 2;
        T1 one = 1;
        while (power)
        {
            if (power % two == one)
                res = res * value;
            value = value * value;
            power /= two;
        }
        return res;
    }

    template <typename T1>
    T1
    unsafeLogPow(T1 value, T1 power)
    {
        T1 res = 1;
        T1 two = 2;
        T1 one = 1;

        while (power)
        {
            if (power % two == one)
                res = res * value;
            value = value * value;
            power /= two;
        }
        return res;
    }

    template <typename T1>
    modNum<T1>
    fpow(modNum<T1> value, T1 power)
    {
        if (value == static_cast<T1>(0) && power == static_cast<T1>(0))
        {
            throw std::invalid_argument("0 pow 0 is undefined");
        }

        return classicLogPow(value, power);
    }
#endif
}