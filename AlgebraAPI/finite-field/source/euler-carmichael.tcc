#include <cmath>
#include <map>
#include <vector>
#include "../mod-math.h"

using namespace std;
namespace modular
{

#ifndef EULER_CARMICAEL
#define EULER_CARMICAEL

    /*
     * @brief Calculates the Euler totient function of a number.
     * @tparam T The type of values stored in modNum.
     * @param n The number to calculate the Euler totient function of.
     * @return The Euler totient function of n.
     */
    template <typename T>
    T EulerFunction(T n)
    {
        if (n <= static_cast<T>(0))
            throw logic_error("Euler totient function is not defiend on non Natural values");

        T res = n;

        for (T p = static_cast<T>(2); p * p <= n; p += static_cast<T>(1))
        {
            if (n % p == static_cast<T>(0))
            {
                while (n % p == static_cast<T>(0))
                    n /= p;
                res -= res / p;
            }
        }

        if (n > static_cast<T>(1))
            res -= res / n;
        return res;
    }
    /*
     * @brief Calculates the Euler totient function of a number.
     * @tparam T The type of values stored in modNum.
     * @param num The number to calculate the Euler totient function of.
     * @return The Euler totient function of num.
     */

    template <typename T>
    modNum<T>
    eulerFunction(modNum<T> num)
    {
        return modNum<T>(static_cast<T>(EulerFunction<T>(num.getValue())), num.getMod());
    }

    template <typename T>
    T mygcd(T a, T b)
    {
        while (b)
        {
            T t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    template <typename T>
    T myLogPow(T value, T power)
    {
        T res = 1;
        T two = 2;
        T one = 1;

        while (power)
        {
            if (power % two == one)
                res = res * value;
            value = value * value;
            power /= two;
        }
        return res;
    }
    /*
     * @brief Calculates the Carmichael function of a number.
     * @tparam T The type of values stored in modNum.
     * @param n The number to calculate the Carmichael function of.
     * @return The Carmichael function of n.
     *
     */
    template <typename T>
    T CarmichaelFunction(T n)
    {
        if (n <= static_cast<T>(0))
            throw logic_error("Euler totient function is not defiend on non Natural values");

        if (n == static_cast<T>(1))
            return static_cast<T>(1);
        std::vector<T> factors;
        for (T i = static_cast<T>(2); i * i <= n; i += static_cast<T>(2))
        {
            T w = static_cast<T>(0);
            while (n % i == static_cast<T>(0))
            {
                w++;
                n /= i;
            }
            if (i == static_cast<T>(2) && w >= static_cast<T>(3))
            {
                T power = myLogPow<T>(i, w - 1);
                factors.push_back((power * (i - 1)) / 2);
            }
            else if (i >= 2 && w > 0)
            {
                T power = myLogPow<T>(i, w - 1);
                factors.push_back(power * (i - 1));
            }
            if (i == 2)
                i--;
        }
        if (n != 1)
            factors.push_back(n - 1);

        T res = 1;
        for (auto i : factors)
            res *= i / mygcd(res, i);
        return res;
    }

#endif

} // namespace modular
