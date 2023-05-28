#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <iostream>
#include <list>
#include <vector>

#include "../finite-field/mod-math.h"

using namespace modular;

#ifndef POLY_NODE_H
#define POLY_NODE_H

/**
 * @brief A class representing a node in a polynomial.
 *
 * The Node class represents a node in a polynomial, which consists of a coefficient
 * and a degree.
 *
 * @tparam T The type of the coefficient.
 */
template <typename T>
class Node
{
protected:
    size_t degree;
    modNum<T> koef;

public:
    /**
     * @brief Default constructor for Node.
     *
     * Constructs a Node object with default values.
     */
    Node();
    /**
     * @brief Constructor for Node with specified coefficient and degree.
     *
     * Constructs a Node object with the specified coefficient and degree.
     *
     * @param koef The coefficient of the node.
     * @param degree The degree of the node.
     */
    Node(modNum<T> koef, size_t degree);
    /**
     * @brief Default destructor for Node.
     */
    ~Node() = default;

    /**
     * @brief Returns the degree of the node.
     *
     * @return The degree of the node.
     */
    size_t deg() const;

    /**
     * @brief Returns the coefficient of the node.
     *
     * @return The coefficient of the node.
     */
    modNum<T> k() const;

    bool operator>(const Node<T> &p2) const;
    bool operator>=(const Node<T> &p2) const;
    bool operator<(const Node<T> &p2) const;
    bool operator<=(const Node<T> &p2) const;
    bool operator!=(const Node<T> &p2) const;

    /**
     * @brief Adds two nodes together.
     *
     * Adds the coefficients of two nodes and returns a new node with the sum.
     *
     * @param p2 The second node to be added.
     * @return A new node representing the sum of the two nodes.
     */
    Node<T> operator+(const Node<T> &p2) const;

    /**
     * @brief Subtracts two nodes.
     *
     * Subtracts the coefficient of the second node from the coefficient of the first node
     * and returns a new node with the difference.
     *
     * @param p2 The second node to be subtracted.
     * @return A new node representing the difference of the two nodes.
     */
    Node<T> operator-(const Node<T> &p2) const;

    /**
     * @brief Assigns the value of another node to this node.
     *
     * Assigns the coefficient and degree of another node to this node.
     *
     * @param p2 The node to assign.
     */

    void operator=(const Node<T> &p2);

    bool operator==(const Node<T> &p2) const;

    /**
     * @brief Evaluates the node for a given value.
     *
     * Evaluates the node by substituting the given value for the variable.
     *
     * @param value The value to substitute for the variable.
     * @return The evaluated value of the node.
     */
    modNum<T> evaluate(T) const;
};
#endif

/*
 * @brief A class representing a polynomial.
 *
 * The Polynomial class represents a polynomial, which consists of a list of nodes.
 *
 * @tparam T The type of the coefficients.
 *
 */

/**
 *
 *    @brief A class representing a polynomial with coefficients of type T.
 *    This class provides functionality for manipulating and performing operations on polynomials.
 *    The coefficients of the polynomial are stored as a linked list of nodes, where each node represents a term
 *    in the polynomial.
 *    @tparam T The type of coefficients in the polynomial.
 */
template <typename T>
class Polynomial
{
protected:
    std::list<Node<T>> poly;
    size_t degree = 0;
    T numMod = 0;
    /*
     * @brief Returns the coefficient of the node with the specified degree.
     *
     * Returns the coefficient of the node with the specified degree.
     *
     * @param power The degree of the node.
     * @return The coefficient of the node.
     *
     */
    modNum<T> getCoeff(const size_t power);
    /*
     *@brief copy the polynomial
     *
     * copy the polynomial
     *
     * @return the copy of the polynomial
     */
    Polynomial<T> copy() const;
    /*
     * @brief Shifts the polynomial to the right by the specified number of positions.
     *
     * Shifts the polynomial to the right by the specified number of positions.
     *
     * @param positions The number of positions to shift the polynomial.
     * @return The shifted polynomial.
     */

    Polynomial<T> shiftRight(int positions) const;

public:
    /**
     * @brief Constructor for Polynomial with specified modulus.
     *
     * Constructs a Polynomial object with the specified modulus.
     *
     * @param mod The modulus of the polynomial.
     * @throw std::invalid_argument if the modulus is not prime.
     */
    Polynomial(T mod)
    {
        if (isPrime(modNum<T>(mod, mod + 1), 1000))
            numMod = mod;
        else
            throw std::invalid_argument("Mod should be prime");
    };
    /**
     * @brief Default constructor for Polynomial.
     */
    Polynomial() = default;

    /**
     * @brief Constructor for Polynomial with specified coefficients and modulus.
     *
     * Constructs a Polynomial object with the specified coefficients and modulus.
     *
     * @param vec A vector of pairs representing the coefficients and degrees of the polynomial.
     * @param mod The modulus of the polynomial.
     * @throw std::invalid_argument if the modulus is not prime.
     */

    Polynomial(std::vector<std::pair<T, size_t>> vec, T mod);
    /**
     * @brief Constructor for Polynomial with specified coefficients and modulus.
     *
     * Constructs a Polynomial object with the specified coefficients and modulus.
     *
     * @param arr The array of coefficient-degree pairs.
     * @param n The number of coefficient-degree pairs.
     * @param mod The modulus of the polynomial.
     */
    Polynomial(std::pair<T, size_t> *arr, size_t n, T);
    /**
     * @brief Destructor for Polynomial.
     */
    ~Polynomial() = default;

    /**
     * @brief Constructs a cyclotomic polynomial.
     *
     * Constructs a cyclotomic polynomial of the specified order with the given modulus.
     *
     * @param order The order of the cyclotomic polynomial.
     * @param mod The modulus of the polynomial.
     */
    void fromCyclotomic(size_t order, T mod);

    /**
     * @brief Returns the node at the specified index.
     *
     * Returns the node at the specified index in the polynomial.
     *
     * @param i The index of the node.
     * @return The node at the specified index.
     */
    Node<T> operator[](const size_t i); // use only when really necessary

    bool empty();

    /**
     * @brief Returns an iterator pointing to the beginning of the polynomial.
     *
     * @return An iterator pointing to the beginning of the polynomial.
     */
    typename std::list<Node<T>>::const_iterator begin() const { return poly.begin(); };

    /**
     * @brief Returns an iterator pointing to the end of the polynomial.
     *
     * @return An iterator pointing to the end of the polynomial.
     */
    typename std::list<Node<T>>::const_iterator end() const { return poly.end(); };

    /**
     * @brief Adds a node to the polynomial.
     *
     * Adds the specified node to the polynomial.
     *
     * @param node The node to add.
     */
    void addNode(const Node<T>);

    /**
     * @brief Adds a node with the specified coefficient and degree to the polynomial.
     *
     * Adds a node with the specified coefficient and degree to the polynomial.
     *
     * @param coefficient The coefficient of the node.
     * @param degree The degree of the node.
     */
    void addNode(const T, size_t);

    /**
     * @brief Removes a node from the polynomial by value.
     *
     * Removes the specified node from the polynomial by value.
     *
     * @param node The node to remove.
     */
    void removeNode(const Node<T>); // by value
    /**
     * @brief Removes a node from the polynomial by degree.
     *
     * Removes the node with the specified degree from the polynomial.
     *
     * @param degree The degree of the node to remove.
     */
    void removeNode(const size_t); // by degree

    /**
     * @brief Returns the degree of the polynomial.
     *
     * Returns the degree of the polynomial.
     *
     * @return The degree of the polynomial.
     */
    size_t getDegree() const
    {
        if (poly.empty())
            return std::numeric_limits<int>::min();
        else
            return degree;
    };

    /**
     * @brief Returns the modulus of the polynomial.
     *
     * Returns the modulus of the polynomial.
     *
     * @return The modulus of the polynomial.
     */
    T getNumMod() const { return numMod; }

    /**
     * @brief Converts the polynomial to a vector representation.
     *
     * Converts the polynomial to a vector representation with coefficient-degree pairs.
     *
     * @return A vector of coefficient-degree pairs representing the polynomial.
     */
    std::vector<std::pair<T, size_t>> toPolyVector();

    /**
     * @brief Prints the polynomial.
     */
    void print() const;

    /**
     * @brief Returns a string representation of the polynomial.
     *
     * Returns a string representation of the polynomial.
     *
     * @return A string representation of the polynomial.
     */
    std::string toString() const;

    /**
     * @brief Returns the size of the polynomial.
     *
     * Returns the number of nodes in the polynomial.
     *
     * @return The size of the polynomial.
     */
    size_t size() const { return poly.size(); };

    //////////////////////////////////////////////////////////////////////////////
    /**
     * @brief Overloaded addition operator.
     *
     * Performs the addition of two polynomials and returns the result as a new polynomial.
     *
     * @param other The polynomial to be added.
     * @return A new polynomial representing the sum of the two polynomials.
     */

    Polynomial<T> operator+(const Polynomial<T> &) const;

    /**
     * @brief Overloaded subtraction operator.
     *
     * Performs the subtraction of two polynomials and returns the result as a new polynomial.
     *
     * @param other The polynomial to be subtracted.
     * @return A new polynomial representing the difference between the two polynomials.
     */
    Polynomial<T> operator-(const Polynomial<T> &) const;
    /**
     * @brief Overloaded multiplication operator.
     *
     * Performs the multiplication of two polynomials and returns the result as a new polynomial.
     *
     * @param other The polynomial to be multiplied.
     * @return A new polynomial representing the product of the two polynomials.
     */
    Polynomial<T> operator*(const Polynomial<T> &) const;
    /**
     * @brief Overloaded equality operator.
     *
     * Checks if two polynomials are equal.
     *
     * @param other The polynomial to be compared with.
     * @return True if the two polynomials are equal, false otherwise.
     */
    bool operator==(const Polynomial<T> &) const;

    //////////////////////////////////////////////////////////////////////////////
    /**
     * @brief Calculate the derivative of the polynomial.
     *
     * Returns a new polynomial that represents the derivative of the current polynomial.
     *
     * @return The derivative polynomial.
     */
    Polynomial<T> der() const;
    /**
     * @brief Evaluate the polynomial at a specific value.
     *
     * Evaluates the polynomial at the given value and returns the result as a modNum<T> object.
     *
     * @param value The value at which to evaluate the polynomial.
     * @return The result of the polynomial evaluation as a modNum<T> object.
     */
    modNum<T> evaluate(const T) const;

    /**
     * @brief Evaluate the polynomial at a specific value.
     *
     * Evaluates the polynomial at the given value and returns the result as a modNum<T> object.
     *
     * @param value The value at which to evaluate the polynomial as a modNum<T> object.
     * @return The result of the polynomial evaluation as a modNum<T> object.
     */
    modNum<T> evaluate(const modNum<T>) const;

    //////////////////////////////////////////////////////////////////////////////

    /**
     * @brief Perform polynomial division using the classic algorithm.
     *
     * Divides the current polynomial by the divisor polynomial using the classic division algorithm.
     * Returns a pair of polynomials representing the quotient and remainder.
     *
     * @param divisor The polynomial divisor.
     * @return A pair of polynomials representing the quotient and remainder.
     */
    std::pair<Polynomial<T>, Polynomial<T>> divClassic(const Polynomial<T> &) const;

    /**
     * @brief Perform polynomial division using the classic algorithm.
     *
     * Divides the current polynomial by the divisor using the classic division algorithm.
     * Returns a pair of polynomials representing the quotient and remainder.
     *
     * @param divisor The divisor as a modNum<T> object.
     * @return A pair of polynomials representing the quotient and remainder.
     */
    std::pair<Polynomial<T>, Polynomial<T>> divClassic(const modNum<T> &) const;

    /**
     * @brief Overloaded modulo operator.
     *
     * Divides the current polynomial by the divisor polynomial and returns the remainder as a new polynomial.
     *
     * @param divisor The polynomial divisor.
     * @return The remainder polynomial.
     */
    Polynomial<T> operator/(const Polynomial<T> &) const;

    /**
     * @brief Overloaded modulo operator.
     *
     * Divides the current polynomial by the divisor polynomial and returns the remainder as a new polynomial.
     *
     * @param divisor The polynomial divisor.
     * @return The remainder polynomial.
     */
    Polynomial<T> operator%(const Polynomial<T> &) const;

    /**
     * @brief Overloaded modulo operator.
     *
     * Divides the current polynomial by the divisor and returns the remainder as a new polynomial.
     *
     * @param divisor The divisor as a modNum<T> object.
     * @return The remainder polynomial.
     */

    Polynomial<T> operator%(const modNum<T> &) const;
    /**
     * @brief Overloaded division operator.
     *
     * Divides the current polynomial by the divisor and returns the quotient as a new polynomial.
     *
     * @param divisor The divisor as a modNum<T> object.
     * @return The quotient polynomial.
     */
    Polynomial<T> operator/(const modNum<T> &) const;
    /**
     * @brief Compute the greatest common divisor of two polynomials.
     *
     * Computes the greatest common divisor (GCD) of the current polynomial and the given polynomial.
     * Returns the GCD polynomial.
     *
     * @param other The polynomial to compute the GCD with.
     * @return The GCD polynomial.
     */
    Polynomial<T> gcd(const Polynomial<T> &) const;

    //////////////////////////////////////////////////////////////////////////////
    /**
     * @brief Returns a polynomial of the specified order.
     *
     * Returns a polynomial of the specified order, where the coefficients are all ones.
     *
     * @param order The order of the polynomial.
     * @return A polynomial of the specified order.
     */
    static Polynomial<T> getPolynomialByOrder(size_t);
};

#include "source/circular-polynomial.tcc"
#include "source/constructors.tcc"
#include "source/divAndGcd.tcc"
#include "source/node.tcc"
#include "source/poly-basic.tcc"
#include "source/utils.tcc"
#endif