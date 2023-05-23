#ifndef MOD_NUM
#define MOD_NUM

#include <stdexcept>
#include <string>
#include <vector>

namespace modular
{

    template <typename T>
    class modNum
    {
    private:
        mutable T value, MOD;

        T add(T value1, T value2, T MOD) const;
        T subs(T value1, T value2, T MOD) const;
        T mult(T value1, T value2, T MOD) const;
        T inverseValue(T value1, T mod) const;
        T div(T value1, T value2, T mod) const;

    public:
        modNum(T _value = 0, T _MOD = 1)
        {
            if (_MOD <= 0)
            {
                throw std::invalid_argument("modulus should be positive");
            }
            value = (_value % _MOD + _MOD) % _MOD;
            MOD = _MOD;
        }

        T getValue() const;
        T getMod() const { return MOD; };
        void setMod(T MOD);
        void setValue(T value);

        bool operator==(const modNum<T> &other) const
        {
            return value == other.value && MOD == other.MOD;
        }

        bool operator<(const modNum<T> &other) const { return value < other.value; }

        bool operator<=(const modNum<T> &other) const { return value <= other.value; }

        bool operator>(const modNum<T> &other) const { return value > other.value; }

        bool operator>=(const modNum<T> &other) const { return value >= other.value; }

        modNum<T> inv();

        modNum<T> operator+(const modNum<T> &other) const;
        modNum<T> operator-(const modNum<T> &other) const;
        modNum<T> operator*(const modNum<T> &other) const;
        modNum<T> operator/(const modNum<T> &other) const;

        // Strategy pattern
        template <typename T1>
        class Factorization
        {
        public:
            virtual ~Factorization() = default;
            virtual std::vector<T1> factor(T1 value) = 0;
        };

        template <typename T1>
        class Pollard : public Factorization<T1>
        {
        public:
            std::vector<T1> factor(T1 value) override;
        };

        template <typename T1>
        class Naive : public Factorization<T1>
        {
        public:
            std::vector<T1> factor(T1 m) override;
        };

    private:
        Factorization<T> *levelStrat;

    public:
        void setStrat(Factorization<T> *strat)
        {
            levelStrat = strat;
        }

        std::vector<T> factorize()
        {
            std::vector<T> factors = levelStrat->factor(this->getValue());

            return factors;
        }

        T gcdExtended(T a, T b, T *x, T *y) const;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1>
    modNum<T1> pow(modNum<T1> value, modNum<T1> base,
                   modNum<T1> MOD); // regular pow
    template <typename T1>
    modNum<T1> fpow(modNum<T1> value, T1 degree); // fast pow

    template <typename T>
    modNum<T> fpowMontogomery(modNum<T> value, T power);
    //////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T1>
    std::vector<modNum<T1>> factorize(
        modNum<T1> value); // number factorization using Polard algorithm

    template <typename T1>
    std::vector<modNum<T1>> naiveFactorize(
        modNum<T1> value); // number factorization using naive algorithm

    //////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T1>
    std::vector<T1> sqrt(modNum<T1> value); // discrete square root

    //////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1>
    T1 log(modNum<T1> value,
           modNum<T1> base); // discrete logarithm

    //////////////////////////////////////////////////////////////////////////////////////////////

    // needs clarifications
    template <typename T1>
    bool isGenerator(modNum<T1> value); // is element a multyplicative group generator

    template <typename T1>
    T1 orderOfElement(modNum<T1> value);

    //////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    modNum<T> eulerFunction(modNum<T> num); // Euler function

    template <typename T1>
    T1 carmichaelFunction(T1 value); // Carmichael function

    //////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1>
    bool isPrime(modNum<T1> value, size_t k); // Miller–Rabin primality test

} // namespace modular

#include "source/euler-carmichael.tcc"
#include "source/factorization.tcc"
#include "source/fpow.tcc"
#include "source/isGenerator.tcc"
#include "source/isPrime.tcc"
#include "source/log.tcc"
#include "source/mod-num.tcc"
#include "source/orderOfElement.tcc"
#include "source/sqrt.tcc"

#endif
