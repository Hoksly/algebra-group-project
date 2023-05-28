#ifndef CYCLATOMIC_TCC
#define CYCLATOMIC_TCC

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "../poly-ring-math.h"

/**
 * Subtracts two vectors representing polynomials.
 *
 * @param p The first polynomial vector.
 * @param q The second polynomial vector.
 * @return The result of subtracting p from q.
 */
template <typename T>
std::vector<T>
subtract(const std::vector<T> &p, const std::vector<T> &q) {
    std::vector<T> v(p);
    v.resize(std::max(p.size(), q.size()));

    for (size_t n = 0; n < q.size(); ++n) {
        v.at(q.size() - 1 - n) -= q.at(q.size() - 1 - n);
    }
    while (!v.empty() && v.back() == 0) {
        v.pop_back();
    }
    return v;
}

/**
 * Multiplies two vectors representing polynomials using the FOIL method.
 *
 * @param p The first polynomial vector.
 * @param q The second polynomial vector.
 * @return The result of multiplying p by q.
 */
template <typename T>
std::vector<T>
multiply_foil(const std::vector<T> &p, const std::vector<T> &q) {
    /* this version of multiply uses the foil method */
    std::vector<T> v(p.size() + q.size(), 0);
    for (size_t n = 0; n < p.size(); ++n) {
        for (size_t m = 0; m < q.size(); ++m) {
            v.at(n + m) += p.at(n) * q.at(m);
        }
    }
    while (!v.empty() && v.back() == 0) {
        v.pop_back();
    }
    return v;
}

/**
 * Divides two vectors representing polynomials.
 *
 * @param p The dividend polynomial vector.
 * @param q The divisor polynomial vector.
 * @return The result of dividing p by q.
 */
template <typename T>
std::vector<T>
divide(std::vector<T> p, std::vector<T> q) {
    std::vector<T> terms(std::max(p.size(), q.size()) + 1, 0);
    while ((p.size() == q.size() && p.back() == q.back()) ||
           (p.size() > q.size() || p.back() > q.back())) {
        std::vector<T> term(p.size() - q.size() + 1, 0);

        term.at(term.size() - 1) = terms.at(term.size() - 1) = p.back() / q.back();

        p = subtract(
            p,
            multiply_foil(
                q, term));   //(p.size() == q.size() ? multiply(q, term) : multiply_foil(q, term))
        if (p.empty()) {
            break;
        }
    }
    while (!terms.empty() && terms.back() == 0) {
        terms.pop_back();
    }
    return terms;
}

/**
 * Computes the cyclotomic polynomial of order N.
 *
 * @param N The order of the cyclotomic polynomial.
 * @return The cyclotomic polynomial as a vector.
 */
template <typename T>
vector<T>
getCyclotomicPolynomialRaw(size_t N) {
    static std::unordered_map<size_t, std::vector<T>> cache;
    if (N == 1) {
        return std::vector<T>({1, -1});
    }
    if (cache.count(N) > 0) {
        return cache.at(N);
    }
    std::function<bool(size_t)> prime = [](size_t p) -> bool {
        if (p <= 1) {
            return false;
        }
        if (p <= 3) {
            return true;
        }
        if (p % 2 == 0) {
            return false;
        }
        size_t m = static_cast<size_t>(sqrt(p)) + 1;
        for (size_t i = 3; i <= m; i += 2) {
            if (p % i == 0) {
                return false;
            }
        }
        return true;
    };

    std::function<bool(size_t, size_t)> power_of = [](size_t x, size_t p) -> bool {
        while (!(x % p) && x > 1) {
            x /= p;
        }
        return x == 1;
    };
    std::vector<T> v;
    if (prime(N)) {
        v.resize(N, 1);

    } else if ((N % 2 == 0) && ((N / 2) % 2 != 0) && prime(N / 2)) {
        size_t n = N / 2;
        v.reserve(n);
        for (size_t i = 0; i < n; ++i) {
            v.push_back((!(i % 2)) ? 1 : -1);
        }
    } else if (N > 1 && power_of(N, 2)) {
        v.resize(static_cast<size_t>(N / 2) + 1);
        v.at(0) = 1;
        v.at(v.size() - 1) = 1;
    } else if (((N % 12 == 0) && power_of(N / 12, 2)) || ((N % 18 == 0) && power_of(N / 18, 2))) {
        v.resize(static_cast<size_t>(N / 3) + 1);
        v.at(0) = 1;
        v.at(v.size() / 2) = -1;
        v.at(v.size() - 1) = 1;
    } else if ((N % 9 == 0) && power_of(N, 3)) {
        v.resize(static_cast<size_t>(N / 1.5) + 1);
        v.at(0) = 1;
        v.at(v.size() / 2) = 1;
        v.at(v.size() - 1) = 1;
    } else {
        std::vector<T> q = {1};

        // factors of N
        for (size_t i = 1, n = N / 2; i <= n; ++i) {
            if (N % i == 0) {
                std::vector<T> p = getCyclotomicPolynomialRaw<T>(i);
                q = multiply_foil(q, std::vector<T>(p.rbegin(), p.rend()));
            }
        }

        std::vector<T> p(static_cast<size_t>(N) + 1, 0);

        p.at(0) = -1;
        p.at(p.size() - 1) = 1;

        v = divide(p, q);
        std::reverse(v.begin(), v.end());
        cache.emplace(N, v);
    }
    return v;
}

/**
 * @brief Initializes the polynomial from the N-th cyclotomic polynomial modulo mod.
 *
 * This function initializes the polynomial from the N-th cyclotomic polynomial modulo mod.
 * The cyclotomic polynomial is first computed using the
 * getCyclotomicPolynomialRaw function, and then the coefficients
 * are added to the polynomial using the addNode function.
 *
 * @tparam T The type of the coefficients and modulus.
 * @param N The index of the cyclotomic polynomial to use.
 * @param mod The modulus to use for the coefficients.
 */
template <typename T>
void
Polynomial<T>::fromCyclotomic(size_t N, T mod) {
    vector<T> v;
    this->numMod = mod;
    if (N == 1) {
        v = std::vector<T>({1, -1});
    } else {
        v = getCyclotomicPolynomialRaw<T>(N);
    }

    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ' ' << i << std::endl;
        this->addNode((v[i] + mod) % mod, i);
    }
}

#endif