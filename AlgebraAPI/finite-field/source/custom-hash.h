#ifndef HASH_MPZ_H_
#define HASH_MPZ_H_

#include <gmpxx.h>
#include <cstddef>
#include <iostream>
#include <unordered_map>

template <>
struct std::hash<mpz_srcptr>
{
    size_t operator()(const mpz_srcptr x) const;
};

template <>
struct std::hash<mpz_t>
{
    size_t operator()(const mpz_t x) const;
};

template <>
struct std::hash<mpz_class>
{
    size_t operator()(const mpz_class &x) const;
};

static constexpr size_t pi_size_t()
{
    if (sizeof(size_t) == 4)
    {
        return 0xc90fdaa2; // floor(pi/4 * 2^32)
    }
    else if (sizeof(size_t) == 8)
    {
        return 0xc90fdaa22168c234; // floor(pi/4 * 2^64)
    }
    else
    {
        throw std::logic_error("this sizeof(size_t) is not supported. only 32 or 64 bits are supported.");
    }
}

static inline size_t scramble(size_t v)
{
    return v ^ (pi_size_t() + (v << 6) + (v >> 2));
}

size_t std::hash<mpz_srcptr>::operator()(const mpz_srcptr x) const
{
    size_t result = 0;

    // Process the limbs directly
    for (mp_size_t i = 0; i < std::abs(x->_mp_size); ++i)
    {
        const mp_limb_t limb = x->_mp_d[i];
        result ^= scramble(static_cast<size_t>(limb));
    }

    // Produce different hashes for negative x
    if (x->_mp_size < 0)
    {
        result = scramble(result);
    }

    return result;
}

size_t std::hash<mpz_t>::operator()(const mpz_t x) const
{
    return hash<mpz_srcptr>{}(static_cast<mpz_srcptr>(x));
}

size_t std::hash<mpz_class>::operator()(const mpz_class &x) const
{
    return hash<mpz_srcptr>{}(x.get_mpz_t());
}

#endif /* HASH_MPZ_H_ */
