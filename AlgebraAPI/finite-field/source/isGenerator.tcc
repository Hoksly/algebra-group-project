#include "factorization.tcc"
#include "mod-num.tcc"

#include <map>
#include <numeric>
#include <utility>

namespace modular
{
#ifndef IS_GENERATOR_TCC
#define IS_GENERATOR_TCC

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

/*

no matching function for call to ‘fpow(modular::modNum<__gmp_expr<__mpz_struct [1], __mpz_struct
[1]> >&, __gmp_expr<__mpz_struct [1],
__gmp_binary_expr<__gmp_expr<__mpz_struct [1], __mpz_struct [1]>, __gmp_expr<__mpz_struct [1],
__mpz_struct [1]>, __gmp_binary_divides> >)’
*/