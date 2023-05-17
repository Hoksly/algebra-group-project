
#include "fpow.tcc"
#include "isGenerator.tcc"
#include "mod-num.tcc"

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace modular
{
#ifndef LOG_H
#define LOG_H

    template <class numT>
    struct customHash
    {
    private:
        std::hash<numT> hasher;

    public:
        size_t operator()(const modNum<numT> &number) const { return hasher(number.getValue()); }
    };

    template <class numT>
    numT
    log(modNum<numT> value, modNum<numT> base)
    {
        if (!isGenerator(base))
            throw std::invalid_argument("Base of a logarithm must be a group Generator");

        numT m = static_cast<numT>(std::sqrt(base.getMod().get_d()));
        while (m * m < base.getMod())
            m++;

        std::unordered_map<modNum<numT>, numT, customHash<numT>> table;

        modNum<numT> basePowed(1, base.getMod());
        for (numT i = 0; i < m; ++i)
        {
            table.insert({basePowed, i});
            basePowed = base * basePowed;
        }

        modNum<numT> alphaInversed = fpow(base.inv(), m);
        modNum<numT> gamma = value;

        for (numT i = 0; i < m; ++i)
        {
            if (table.find(gamma) != table.end())
            {
                std::cout << i << std::endl;
                std::cout << m << std::endl;
                std::cout << table[gamma] << std::endl;

                return i * m + table[gamma];
            }
            gamma = gamma * alphaInversed;
        }

        throw std::invalid_argument("Unexpected behaviour");
    }
#endif

} // namespace modular