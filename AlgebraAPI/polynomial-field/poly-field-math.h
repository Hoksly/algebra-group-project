#ifndef POLY_FIELD
#define POLY_FIELD

#include "../polynomial-ring/poly-ring-math.h"

using namespace modular;

/**
 * @brief Checks if a number is prime using a simple primality test.
 *
 * This function checks if a number is prime by iterating from 2 to the square root
 * of the number and checking if the number is divisible by any of the iterated values.
 * If the number is divisible by any value in the range, it is considered non-prime.
 *
 * @param num The number to be checked for primality.
 * @return True if the number is prime, otherwise false.
 */

template <typename T>
bool isPrimeSimpleFunction(T num)
{
    T check = sqrt(num);

    for (int i = 2; i <= check; i++)
        if (num % i == 0)
            return false;
    return true;
}

/**
 * @brief A vector of nodes.
 *
 * @tparam T The type of elements in the vector.
 */
template <typename T>
typename std::vector<T> nodes;

/**
 * @brief A class representing a polynomial field.
 *
 * The PolynomialField class represents a polynomial field defined over a prime modulus.
 * It provides operations for arithmetic, exponentiation, irreducibility checking,
 * normalization, and more.
 *
 * @tparam T The type of coefficients in the polynomial.
 */
template <typename T>
class PolynomialField
{
protected:
    T numMod;

    Polynomial<T> value;
    Polynomial<T> MOD;

    void correct();

public:
    /**
     * @brief Constructs a PolynomialField object with a prime modulus and a polynomial modulus.
     *
     * Constructs a PolynomialField object with a prime modulus and a polynomial modulus.
     * The value of the PolynomialField is initialized to the default polynomial.
     *
     * @param mod The prime modulus of the polynomial field.
     * @param polyMod The polynomial modulus.
     * @throw std::invalid_argument if the modulus is not prime.
     */
    PolynomialField(T mod, Polynomial<T> polyMod)
    {
        if (isPrimeSimpleFunction(mod))
        {
            this->numMod = mod;
            Polynomial<T> tmp(mod);
            this->value = tmp;
            this->MOD = polyMod;
        }
        else
            throw std::invalid_argument("Mod should be prime");
    }
    /**
     * @brief Constructs a PolynomialField object with a prime modulus, a polynomial modulus, and a polynomial value.
     *
     * Constructs a PolynomialField object with a prime modulus, a polynomial modulus, and a polynomial value.
     *
     * @param mod The prime modulus of the polynomial field.
     * @param polyMod The polynomial modulus.
     * @param polyValue The polynomial value.
     * @throw std::invalid_argument if the modulus is not prime.
     */
    PolynomialField(T mod, Polynomial<T> polyMod, Polynomial<T> polyValue)
    {
        if (isPrimeSimpleFunction(mod))
        {
            this->numMod = mod;
            this->MOD = polyMod;
            this->value = polyValue;
        }
        else
            throw std::invalid_argument("Mod should be prime");
    }
    /**
     * @brief Constructs a PolynomialField object with a prime modulus, a polynomial modulus, and a vector of polynomial nodes.
     *
     * Constructs a PolynomialField object with a prime modulus, a polynomial modulus,
     * and a vector of polynomial nodes representing the polynomial value.
     *
     * @param mod The prime modulus of the polynomial field.
     * @param polyMod The polynomial modulus.
     * @param polyV A vector of polynomial nodes representing the polynomial value.
     * @throw std::invalid_argument if the modulus is not prime.
     */
    PolynomialField(T mod, Polynomial<T> polyMod, std::vector<std::pair<T, size_t>> polyV)
    {
        if (isPrimeSimpleFunction(mod))
        {
            this->numMod = mod;
            this->MOD = polyMod;
            this->value = Polynomial<T>(polyV, mod);
        }
        else
            throw std::invalid_argument("Mod should be prime");
    }
    /**
     * @brief Constructs a PolynomialField object with a prime modulus, vectors of polynomial nodes for the modulus and value.
     *
     * Constructs a PolynomialField object with a prime modulus, vectors of polynomial nodes for the modulus and value.
     *
     * @param mod The prime modulus of the polynomial field.
     * @param modV A vector of polynomial nodes representing the polynomial modulus.
     * @param polyV A vector of polynomial nodes representing the polynomial value.
     * @throw std::invalid_argument if the modulus is not prime.
     */
    PolynomialField(T mod, std::vector<std::pair<T, size_t>> modV,
                    std::vector<std::pair<T, size_t>> polyV)
    {
        if (isPrimeSimpleFunction(mod))
        {
            this->numMod = mod;
            this->MOD = Polynomial<T>(modV, mod);
            this->value = Polynomial<T>(polyV, mod);
        }
        else
            throw std::invalid_argument("Mod should be prime");
    }
    /**
     * @brief Default constructor for PolynomialField.
     */
    PolynomialField() = default;
    /**
     * Adds two PolynomialField objects and returns the result.
     *
     * @param other The PolynomialField to be added.
     * @return The sum of the two PolynomialField objects.
     */
    PolynomialField<T> operator+(const PolynomialField<T> &) const;

    /**
     * Subtracts another PolynomialField object from this object and returns the result.
     *
     * @param other The PolynomialField to be subtracted.
     * @return The difference between the two PolynomialField objects.
     */
    PolynomialField<T> operator-(const PolynomialField<T> &) const;

    /**
     * Multiplies two PolynomialField objects and returns the result.
     *
     * @param other The PolynomialField to be multiplied.
     * @return The product of the two PolynomialField objects.
     */
    PolynomialField<T> operator*(const PolynomialField<T> &) const;

    /**
     * Multiplies the PolynomialField object by a scalar value and returns the result.
     *
     * @param num The scalar value to multiply the PolynomialField object with.
     * @return The product of the PolynomialField object and the scalar value.
     */
    PolynomialField<T> operator*(T num) const;
    /**
     * Checks if the PolynomialField object is equal to another PolynomialField object.
     *
     * @param other The PolynomialField to compare with.
     * @return True if the PolynomialField objects are equal, false otherwise.
     */
    bool operator==(const PolynomialField<T> &) const;

    /**
     * Raises the PolynomialField object to the power of k and returns the result.
     *
     * @param k The exponent to raise the PolynomialField object to.
     * @return The PolynomialField object raised to the power of k.
     */
    PolynomialField<T> pow(T k);
    /**
     * Adds a new node to the PolynomialField object with the given coefficient and degree.
     *
     * @param num The coefficient of the new node.
     * @param deg The degree of the new node.
     */
    void addNode(const T num, size_t deg);
    /**
     * Adds a new node to the PolynomialField object using the given Node object.
     *
     * @param node The Node object representing the new node to be added.
     */
    void addNode(Node<T>);
    /**
     * Returns the Polynomial object stored in the PolynomialField.
     *
     * @return The Polynomial object stored in the PolynomialField.
     */
    Polynomial<T> getValue() { return this->value; }

    /**
     * @brief Converts a cyclotomic polynomial to its multipliers in the given polynomial field.
     *
     * Converts a cyclotomic polynomial to its multipliers in the given polynomial field.
     *
     * @param num The order of the cyclotomic polynomial.
     * @param mod The prime modulus of the polynomial field.
     * @return A vector of PolynomialField objects representing the multipliers of the cyclotomic polynomial.
     */
    static std::vector<PolynomialField<T>> cyclotomicToMultipliers(T num, T mod);
    /**
     * @brief Finds irreducible polynomials of degree k in the polynomial field.
     *
     * Finds irreducible polynomials of degree k in the polynomial field.
     *
     * @param k The degree of the irreducible polynomials to be found.
     * @return A vector of PolynomialField objects representing the irreducible polynomials.
     */
    static std::vector<PolynomialField<T>> findKIrreducible(size_t k);

    /**
     * @brief Checks if the polynomial in the polynomial field is irreducible.
     *
     * Checks if the polynomial in the polynomial field is irreducible.
     *
     * @return True if the polynomial is irreducible, otherwise false.
     */
    bool isIrreducible();

    /**
     * @brief Normalizes the polynomial in the polynomial field.
     *
     * Normalizes the polynomial in the polynomial field by reducing its coefficients
     * modulo the prime modulus.
     */
    void normalize();

    /**
     * @brief Calculates the multiplicative inverse of the polynomial in the polynomial field.
     *
     * Calculates the multiplicative inverse of the polynomial in the polynomial field
     * using the extended Euclidean algorithm.
     *
     * @return The multiplicative inverse of the polynomial.
     */
    PolynomialField<T> inv() const;

    PolynomialField<T> operator/(const PolynomialField<T> &) const;
    /**
     * @brief Calculates the order of the polynomial in the polynomial field.
     *
     * Calculates the order of the polynomial in the polynomial field, which is
     * the smallest positive exponent k such that value^k = 1.
     *
     * @return The order of the polynomial.
     */
    size_t getOrder();

    /**
     * @brief Checks if the polynomial in the polynomial field is a generator.
     *
     * Checks if the polynomial in the polynomial field is a generator,
     * i.e., it generates all nonzero elements of the field.
     *
     * @return True if the polynomial is a generator, otherwise false.
     */
    bool isGenerator();

    /**
     * @brief Prints the polynomial value of the polynomial field.
     */
    void print() { value.print(); }
};

#include "source//poly-field-basic.tcc"
// #include "source//cyclotomicToMultipliers.tcc" -> lots of bugs so have to comment
#include "source/irredicibilityTest.tcc"
#include "source/inverse-poly.tcc"

#endif