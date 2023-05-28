#include <map>
#include <utility>

#include "factorization.tcc"
#include "mod-num.tcc"

namespace modular
{
#ifndef ORDER_OG_ELEMENT
#define ORDER_OG_ELEMENT

    /*
     * @brief Calculates the order of an element in a multiplicative group.
     * @tparam T The type of values stored in modNum.
     * @param a The element to calculate the order of.
     * @return The order of a.
     */
    template <typename T>
    T orderOfElement(modNum<T> a)
    {
        T t = a.getMod();

        modNum<T> a1, one(static_cast<T>(1), a.getMod());

        vector<modNum<T>> factors = factorize(modNum<T>(t - 1, t + 1));

        std::map<modNum<T>, size_t> factorsCombined;

        for (auto factor : factors)
        {
            factorsCombined[factor]++;
        }

        for (auto num : factorsCombined)
        {
            t = t / fpow(num.first, static_cast<T>(num.second)).getValue();
            a1 = fpow(a, t);

            while (!(a1 == one))
            {
                a1 = fpow(a1, num.first.getValue());
                t = (t * num.first.getValue()) % num.first.getMod();
            }
        }

        return t;
    }

#endif

} // namespace modular