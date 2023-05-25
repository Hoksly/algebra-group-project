#include <map>
#include <numeric>
#include <utility>

#include "factorization.tcc"
#include "mod-num.tcc"

namespace modular
{
#ifndef IS_GENERATOR_TCC
#define IS_GENERATOR_TCC

    /*
     * @brief Checks if a number is a generator of a multiplicative group.
     * @tparam T The type of values stored in modNum.
     * @param a The number to check.
     * @return True if a is a generator of a multiplicative group, false otherwise.
     */
    template <typename T>
    bool
    isGenerator(modNum<T> a)
    {
        T t = a.getMod();
        modNum<T> b, one(static_cast<T>(1), a.getMod());

        vector<modNum<T>> factors = factorize(modNum<T>(t - 1, t + 1));

        std::map<modNum<T>, size_t> factorsCombined;

        for (auto factor : factors)
        {
            factorsCombined[factor]++;
        }
        T n = a.getMod(), pi;

        for (auto num : factorsCombined)
        {
            pi = num.first.getValue();
            b = fpow(a, static_cast<T>(n / pi));
            if (b == one)
                return false;
        }
        return true;
    }

#endif

} // namespace modular
