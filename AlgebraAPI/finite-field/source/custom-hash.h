#ifndef HASH_MPZ_H_
#define HASH_MPZ_H_

#include <gmpxx.h>
#include <cstddef>
#include <iostream>
#include <unordered_map>

/**
 * @struct std::hash<mpz_srcptr>
 * @brief Hash specialization for `mpz_srcptr`.
 *
 * This struct provides a hash function for the `mpz_srcptr` type, which is used
 * by hash-based data structures like `std::unordered_map` to compute the hash
 * value of keys of type `mpz_srcptr`.
 */
template <>
struct std::hash<mpz_srcptr>
{ /**
   * @brief Calculates the hash value for an `mpz_srcptr`.
   *
   * This function calculates the hash value for the given `mpz_srcptr` object.
   * It is used by hash-based data structures to determine the bucket in which
   * the object will be stored.
   *
   * @param x The `mpz_srcptr` object for which to calculate the hash value.
   * @return The calculated hash value.
   */
    size_t operator()(const mpz_srcptr x) const;
};

/**
 * @struct std::hash<mpz_t>
 * @brief Hash specialization for `mpz_t`.
 *
 * This struct provides a hash function for the `mpz_t` type, which is used
 * by hash-based data structures like `std::unordered_map` to compute the hash
 * value of keys of type `mpz_t`.
 */

template <>
struct std::hash<mpz_t>
{
    /**
     * @brief Calculates the hash value for an `mpz_t`.
     *
     * This function calculates the hash value for the given `mpz_t` object.
     * It is used by hash-based data structures to determine the bucket in which
     * the object will be stored.
     *
     * @param x The `mpz_t` object for which to calculate the hash value.
     * @return The calculated hash value.
     */
    size_t operator()(const mpz_t x) const;
};

/**
 * @struct std::hash<mpz_class>
 * @brief Hash specialization for `mpz_class`.
 *
 * This struct provides a hash function for the `mpz_class` type, which is used
 * by hash-based data structures like `std::unordered_map` to compute the hash
 * value of keys of type `mpz_class`.
 */
template <>
struct std::hash<mpz_class>
{
    /**
     * @brief Calculates the hash value for an `mpz_class`.
     *
     * This function calculates the hash value for the given `mpz_class` object.
     * It is used by hash-based data structures to determine the bucket in which
     * the object will be stored.
     *
     * @param x The `mpz_class` object for which to calculate the hash value.
     * @return The calculated hash value.
     */
    size_t operator()(const mpz_class &x) const;
};

/**
 * @brief Returns a size_t value representing an approximation of pi.
 *
 * This function returns a size_t value that approximates the mathematical constant pi.
 * The value returned depends on the size of the size_t type. If the size of size_t is 4 bytes (32 bits),
 * the returned value represents floor(pi/4 * 2^32). If the size of size_t is 8 bytes (64 bits),
 * the returned value represents floor(pi/4 * 2^64).
 *
 * @return The approximate value of pi represented as a size_t.
 *
 * @throws std::logic_error If the size of size_t is neither 4 nor 8 bytes, indicating an unsupported platform.
 */

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
/**
 * @brief Scrambles a given size_t value using a bitwise operation.
 *
 * This function takes a size_t value and performs a bitwise XOR operation with the result
 * of several other bitwise operations to produce a scrambled value.
 *
 * @param v The size_t value to be scrambled.
 * @return The scrambled size_t value.
 */
static inline size_t scramble(size_t v)
{
    return v ^ (pi_size_t() + (v << 6) + (v >> 2));
}

/**
 * @brief Computes the hash value for a given `mpz_srcptr` object.
 *
 * This function calculates the hash value for a `mpz_srcptr` object by processing its limbs
 * directly. Each limb is XORed with a scrambled value obtained from the `scramble` function.
 * If the `mpz_srcptr` object is negative, the resulting hash value is further scrambled.
 *
 * @param x A pointer to the `mpz_srcptr` object to be hashed.
 * @return The computed hash value as a size_t.
 */
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
/**
 * @brief Computes the hash value for a given `mpz_t` object.
 *
 * This function calculates the hash value for a `mpz_t` object by converting it to `mpz_srcptr`
 * and invoking the `operator()` function of `std::hash<mpz_srcptr>`. The hash value is computed
 * based on the underlying `mpz_srcptr` representation of the `mpz_t` object.
 *
 * @param x A pointer to the `mpz_t` object to be hashed.
 * @return The computed hash value as a size_t.
 */
size_t std::hash<mpz_t>::operator()(const mpz_t x) const
{
    return hash<mpz_srcptr>{}(static_cast<mpz_srcptr>(x));
}

/**
 * @brief Computes the hash value for a given `mpz_class` object.
 *
 * This function calculates the hash value for a `mpz_class` object by retrieving its underlying
 * `mpz_t` representation using the `get_mpz_t()` member function and invoking the `operator()`
 * function of `std::hash<mpz_srcptr>`. The hash value is computed based on the underlying
 * `mpz_srcptr` representation of the `mpz_class` object.
 *
 * @param x The `mpz_class` object to be hashed.
 * @return The computed hash value as a size_t.
 */

size_t std::hash<mpz_class>::operator()(const mpz_class &x) const
{
    return hash<mpz_srcptr>{}(x.get_mpz_t());
}

#endif /* HASH_MPZ_H_ */
