#ifndef MOD_NUM

#include <stdexcept>
#include <string>
#include <vector>

namespace modular
{

    /**
     *
     * @brief A class representing a modular number with value of type T.
     * This class provides functionality for performing arithmetic operations on modular numbers.
     * @tparam T The type of value in the modular number.
     */
    template <typename T>
    class modNum
    {
    private:
        mutable T value, MOD;

        /**
         * @brief Addition of two values modulo MOD.
         * @param value1 The first value.
         * @param value2 The second value.
         * @param MOD The modulus value.
         * @return The result of the addition modulo MOD.
         */

        T add(T value1, T value2, T MOD) const;

        /**
         * @brief Subtraction of two values modulo MOD.
         * @param value1 The first value.
         * @param value2 The second value.
         * @param MOD The modulus value.
         * @return The result of the subtraction modulo MOD.
         */

        T subs(T value1, T value2, T MOD) const;

        /**
         * @brief Multiplication of two values modulo MOD.
         * @param value1 The first value.
         * @param value2 The second value.
         * @param MOD The modulus value.
         * @return The result of the multiplication modulo MOD.
         */

        T mult(T value1, T value2, T MOD) const;

        /**
         * @brief Calculates the inverse of a value modulo MOD.
         * @param value1 The value.
         * @param mod The modulus value.
         * @return The inverse value modulo MOD.
         */
        T inverseValue(T value1, T mod) const;

        /**
         * @brief Division of two values modulo MOD.
         * @param value1 The numerator.
         * @param value2 The denominator.
         * @param mod The modulus value.
         * @return The result of the division modulo MOD.
         */
        T div(T value1, T value2, T mod) const;

    public:
        /**
         * @brief Constructor for the modNum class.
         * @param _value The initial value.
         * @param _MOD The modulus value.
         * @throws std::invalid_argument if modulus is not positive.
         */
        modNum(T _value = 0, T _MOD = 1)
        {
            if (_MOD <= 0)
            {
                throw std::invalid_argument("modulus should be positive");
            }
            value = (_value % _MOD + _MOD) % _MOD;
            MOD = _MOD;
        }

        /**
         * @brief Getter for the value.
         * @return The current value.
         */
        T getValue() const;

        /**
         * @brief Getter for the modulus value.
         * @return The current modulus value.
         */
        T getMod() const { return MOD; };

        /**
         * @brief Setter for the modulus value.
         * @param MOD The new modulus value to be set.
         */

        void setMod(T MOD);

        /**
         * @brief Setter for the value.
         * @param value The new value to be set.
         */
        void setValue(T value);

        /**
         * @brief Equality comparison operator.
         * @param other The modNum to compare.
         * @return True if the values and modulus are equal, otherwise false.
         */
        bool operator==(const modNum<T> &other) const
        {
            return value == other.value && MOD == other.MOD;
        }
        /**
         * @brief Less than comparison operator.
         * @param other The modNum to compare.
         * @return True if the value is less than the other value, otherwise false.
         */
        bool operator<(const modNum<T> &other) const { return value < other.value; }
        /**
         * @brief Less than or equal to comparison operator.
         * @param other The modNum to compare.
         * @return True if the value is less than or equal to the other value, otherwise false.
         */
        bool operator<=(const modNum<T> &other) const { return value <= other.value; }
        /**
         * @brief Greater than comparison operator.
         * @param other The modNum to compare.
         * @return True if the value is greater than the other value, otherwise false.
         */
        bool operator>(const modNum<T> &other) const { return value > other.value; }
        /**
         * @brief Greater than or equal to comparison operator.
         * @param other The modNum to compare.
         * @return True if the value is greater than or equal to the other value, otherwise false.
         */
        bool operator>=(const modNum<T> &other) const { return value >= other.value; }
        /**
         * @brief Calculates the inverse of the modNum.
         * @return The inverse of the modNum.
         */
        modNum<T> inv();
        /**
         * @brief Addition operator.
         * @param other The modNum to add.
         * @return The result of the addition.
         */
        modNum<T> operator+(const modNum<T> &other) const;
        /**
         * @brief Subtraction operator.
         * @param other The modNum to subtract.
         * @return The result of the subtraction.
         */
        modNum<T> operator-(const modNum<T> &other) const;
        /**
         * @brief Multiplication operator.
         * @param other The modNum to multiply.
         * @return The result of the multiplication.
         */
        modNum<T> operator*(const modNum<T> &other) const;
        /**
         * @brief Division operator.
         * @param other The modNum to divide by.
         * @return The result of the division.
         */
        modNum<T> operator/(const modNum<T> &other) const;

        /**
         * @brief Abstract base class for factorization strategies.
         */
        template <typename T1>
        class Factorization
        {
        public:
            /**
             * @brief Virtual destructor for Factorization.
             */
            virtual ~Factorization() = default;
            /**
             * @brief Factorizes a value.
             * @param value The value to factorize.
             * @return A vector of factors.
             */
            virtual std::vector<T1> factor(T1 value) = 0;
        };
        /**
         * @brief Implementation of the Pollard factorization strategy.
         */
        template <typename T1>
        class Pollard : public Factorization<T1>
        {
        public:
            /**
             * @brief Factorizes a value using the Pollard strategy.
             * @param value The value to factorize.
             * @return A vector of factors.
             */
            std::vector<T1> factor(T1 value) override;
        };

        /**
         * @brief Implementation of the Naive factorization strategy.
         */
        template <typename T1>
        class Naive : public Factorization<T1>
        {
        public:
            /**
             * @brief Factorizes a value using the Naive strategy.
             * @param m The value to factorize.
             * @return A vector of factors.
             */
            std::vector<T1> factor(T1 m) override;
        };

    private:
        Factorization<T> *levelStrat;

    public:
        /**
         * @brief Sets the factorization strategy.
         * @param strat The factorization strategy to set.
         */
        void setStrat(Factorization<T> *strat)
        {
            levelStrat = strat;
        }
        /**
         * @brief Performs factorization using the selected strategy.
         * @return A vector of factors.
         */
        std::vector<T> factorize()
        {
            std::vector<T> factors = levelStrat->factor(this->getValue());

            return factors;
        }
        /**
         * @brief Calculates the extended GCD of two values.
         * @param a The first value.
         * @param b The second value.
         * @param x Pointer to the variable to store the x coefficient.
         * @param y Pointer to the variable to store the y coefficient.
         * @return The GCD of the two values.
         */
        T gcdExtended(T a, T b, T *x, T *y) const;
    };

    /**
     * @brief Computes the power of a modNum value to a given base modNum.
     * @param value The value to be raised to the power.
     * @param base The base value.
     * @param MOD The modulus value.
     * @return The result of raising value to the power of base modulo MOD.
     */
    template <typename T1>
    modNum<T1> pow(modNum<T1> value, modNum<T1> base, modNum<T1> MOD);

    /**
     * @brief Computes the fast power of a modNum value to a given degree.
     * @param value The value to be raised to the power.
     * @param degree The degree value.
     * @return The result of raising value to the power of degree.
     */
    template <typename T1>
    modNum<T1> fpow(modNum<T1> value, T1 degree);

    /**
     * @brief Computes the fast power of a modNum value using Montgomery multiplication.
     * @param value The value to be raised to the power.
     * @param power The power value.
     * @return The result of raising value to the power using Montgomery multiplication.
     */
    template <typename T>
    modNum<T> fpowMontgomery(modNum<T> value, T power);

    /**
     * @brief Factorizes a modNum value using the Pollard algorithm.
     * @param value The value to factorize.
     * @return A vector of factorized modNum values.
     */
    template <typename T1>
    std::vector<modNum<T1>> factorize(modNum<T1> value);

    /**
     * @brief Factorizes a modNum value using the naive algorithm.
     * @param value The value to factorize.
     * @return A vector of factorized modNum values.
     */
    template <typename T1>
    std::vector<modNum<T1>> naiveFactorize(modNum<T1> value);

    /**
     * @brief Computes the square root of a modNum value.
     * @param value The value to compute the square root.
     * @return A vector of modNum values representing the square root.
     */
    template <typename T1>
    std::vector<T1> sqrt(modNum<T1> value);

    /**
     * @brief Computes the discrete logarithm of a modNum value to a given base.
     * @param value The value for which to compute the discrete logarithm.
     * @param base The base value.
     * @return The discrete logarithm of value with respect to base.
     */
    template <typename T1>
    T1 log(modNum<T1> value, modNum<T1> base);

    /**
     * @brief Checks if a modNum value is a multiplicative group generator.
     * @param value The value to check.
     * @return True if the value is a generator, otherwise false.
     */
    template <typename T1>
    bool isGenerator(modNum<T1> value);

    /**
     * @brief Computes the Euler's totient function of a modNum value.
     * @param num The value for which to compute the Euler's totient function.
     * @return The Euler's totient function value of num.
     */
    template <typename T>
    modNum<T> eulerFunction(modNum<T> num);

    /**
     * @brief Computes the Carmichael function of a value.
     * @param value The value for which to compute the Carmichael function.
     * @return The Carmichael function value of value.
     */
    template <typename T1>
    T1 carmichaelFunction(T1 value);

    /**
     * @brief Performs the Miller-Rabin primality test on a modNum value.
     * @param value The value to test for primality.
     * @param k The number of iterations for the test.
     * @return True if value is likely prime, otherwise false.
     */
    template <typename T1>
    bool isPrime(modNum<T1> value, size_t k);

} // namespace modular
#define MOD_NUM

#include "source/euler-carmichael.tcc"
#include "source/factorization.tcc"
#include "source/fpow.tcc"
#include "source/isGenerator.tcc"
#include "source/isPrime.tcc"
#include "source/log.tcc"
#include "source/mod-num.tcc"
#include "source/sqrt.tcc"

#endif
