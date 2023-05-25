#ifndef POLY_BASICS_IMPLEMENTATION
#define POLY_BASICS_IMPLEMENTATION

#include <cmath>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

#include "../poly-ring-math.h"

using namespace modular;

template <typename T>
Node<T>
Polynomial<T>::operator[](const size_t i)
{
    if (i < 0 || i >= poly.size())
        throw std::out_of_range("Index out of range");

    int j = 0;
    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        if (i == j)
            return *it;
        j++;
    }

    throw std::out_of_range("Index out of range");
}

template <typename T>
std::ostream &
operator<<(std::ostream &os, Node<T> &p)
{
    return os << '{' << p.deg() << ", " << p.k().getValue() << '}';
}

template <typename T>
Polynomial<T>
Polynomial<T>::der() const
{
    Polynomial<T> returned_field;
    Node<T> current_newnode;
    modNum<T> new_koef;
    size_t new_pow;

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        new_koef = (it->k() * modNum<T>(static_cast<T>(it->deg()), this->numMod));
        new_pow = (it->deg() == 0 ? 0 : it->deg() - 1);

        if (new_koef.getValue() > 0)
        {
            current_newnode = Node<T>(new_koef, new_pow);
            returned_field.addNode(current_newnode);
        }
    }

    return returned_field;
}

template <typename T>
modNum<T>
Polynomial<T>::evaluate(const T x_value) const
{
    modNum<T> sum(0, numMod);
    modNum<T> current_num(0, numMod);

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        if (it->deg() > 0)
        {
            T nodeDegree = static_cast<T>(it->deg());
            current_num = fpow(modNum<T>(x_value, numMod), nodeDegree) * it->k();
        }
        else
        {
            current_num = it->k();
        }
        sum = sum + current_num;
    }

    return sum;
}

template <typename T>
modNum<T>
Polynomial<T>::evaluate(const modNum<T> x_value) const
{
    return evaluate(x_value->getValue());
}

template <typename T>
void Polynomial<T>::print() const
{
    // boolean used for adding the plus sign
    bool first_number_checked = false;
    if (poly.empty())
    {
        std::cout << 0;
        return;
    }

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        if (first_number_checked)
        {
            std::cout << " + ";
        }

        else
        {
            first_number_checked = true;
        }
        if (it->deg() > 0)
        {
            if (it->k().getValue() > 1)
                std::cout << (it->k().getValue()) << "x^" << (it->deg());
            else
                std::cout << "x^" << (it->deg());
        }
        else
        {
            std::cout << (it->k().getValue());
        }
    }
    std::cout << std::endl;
}

/*
 * @brief Adds a node to the polynomial.
 * @param node The node to add to the polynomial.
 */

template <typename T>
void Polynomial<T>::addNode(const Node<T> node)
{
    if (node.deg() > degree)
    {
        degree = node.deg();
        poly.push_front(node);
        return;
    }

    for (auto it = poly.begin(); it != poly.end(); it++)
    {
        if (it->deg() == node.deg())
        {
            *it = *it + node;
            return;
        }
        if (it->deg() < node.deg())
        {
            poly.insert(it, node);
            return;
        }
    }
    poly.push_back(node);
}

/*
 * @brief Adds a node to the polynomial.
 * @param num The number to add to the polynomial.
 * @param deg The degree of the number to add to the polynomial.
 */

template <typename T>
void Polynomial<T>::addNode(const T num, size_t deg)
{
    if (static_cast<T>(((num + numMod) % numMod) > 0))
    {
        Node<T> a(modNum<T>(((num + numMod) % numMod), numMod), deg);
        this->addNode(a);
    }
}

/**
 * @brief Adds two polynomials.
 * @param other The polynomial to add to the current polynomial.
 * @return Polynomial<T> The result of adding two polynomials.
 */
template <typename T> // mpz_class libGMP
Polynomial<T>
Polynomial<T>::operator+(const Polynomial<T> &other) const
{
    Polynomial<T> result(this->numMod);
    result.degree = std::max(this->degree, other.degree);

    auto it = this->poly.begin();
    auto io = other.poly.begin();

    while (it != this->poly.end() && io != other.poly.end())
    {
        if (it->deg() == io->deg())
        {
            modNum<T> t1 = it->k();
            modNum<T> t2 = io->k();
            modNum<T> temp = t1 + t2;
            if (temp.getValue() != 0)
                result.addNode(temp.getValue(), it->deg());
            it++;
            io++;
        }
        else if (it->deg() > io->deg())
        {
            modNum<T> t = it->k();
            modNum<T> temp = t;
            result.addNode(temp.getValue(), it->deg());
            it++;
        }
        else
        {
            modNum<T> t = io->k();
            modNum<T> temp = t;
            result.addNode(temp.getValue(), io->deg());
            io++;
        }
    }
    while (it != this->poly.end())
    {
        modNum<T> t = it->k();
        modNum<T> temp = t + (modNum<T>(0));
        result.addNode(temp.getValue(), it->deg());
        it++;
    }
    while (io != other.poly.end())
    {
        modNum<T> t = io->k();
        modNum<T> temp = t + (modNum<T>(0));
        result.addNode(temp.getValue(), io->deg());
        io++;
    }
    return result;
}

/**
 * @brief Subtracts one polynomial from another.
 * @param other The polynomial to subtract from the current polynomial.
 * @return Polynomial<T> The result of subtracting two polynomials.
 */
template <typename T>
Polynomial<T>
Polynomial<T>::operator-(const Polynomial<T> &other) const
{
    Polynomial<T> result(this->numMod);

    auto it = this->poly.begin();
    auto io = other.poly.begin();

    while (it != this->poly.end() && io != other.poly.end())
    {
        if (it->deg() == io->deg())
        {
            modNum<T> t1 = it->k();
            modNum<T> t2 = io->k();
            modNum<T> temp = t1 - (t2);

            if (temp.getValue() != 0)
                result.addNode(temp.getValue(), it->deg());

            it++;
            io++;
        }
        else if (it->deg() > io->deg())
        {
            modNum<T> t = it->k();
            modNum<T> temp = t + (modNum<T>(0));
            result.addNode(temp.getValue(), it->deg());
            it++;
        }
        else
        {
            modNum<T> t = io->k();
            modNum<T> temp = (modNum<T>(0, numMod)) - t;
            result.addNode(temp.getValue(), io->deg());
            io++;
        }
    }
    while (it != this->poly.end())
    {
        modNum<T> t = it->k();
        modNum<T> temp = t + (modNum<T>(0));
        result.addNode(temp.getValue(), it->deg());
        it++;
    }
    while (io != other.poly.end())
    {
        modNum<T> t = io->k();
        modNum<T> temp = (modNum<T>(0, numMod)) - t;
        result.addNode(temp.getValue(), io->deg());
        io++;
    }

    return result;
}

/**
 * @brief Multiplies two polynomials.
 * @param other A polynomial to multiply by the current polynomial.
 * @return Polynomial<T> The result of multiplying two polynomials.
 */
template <typename T>
Polynomial<T>
Polynomial<T>::operator*(const Polynomial<T> &other) const
{
    if (this->getNumMod() != other.getNumMod())
    {
        throw std::invalid_argument("Can't add Polynomials with diferent modulas");
    }
    if (this->poly.empty() || other.poly.empty())
    {
        Polynomial<T> result(this->numMod);
        return result;
    }

    std::size_t s = this->poly.size() + other.poly.size() - 1;
    Polynomial<T> result(this->numMod);
    result.degree = s - 1;
    auto it = this->poly.begin();

    while (it != this->poly.end())
    {
        auto io = other.poly.begin();
        while (io != other.poly.end())
        {
            modNum<T> t1 = it->k();
            modNum<T> t2 = io->k();
            modNum<T> temp = t1 * t2;
            result.addNode(Node<T>(temp, it->deg() + io->deg()));
            io++;
        }
        it++;
    }

    auto temp = result.poly.begin();
    while (temp != result.poly.end())
    {
        if ((temp->k()).getValue() == 0)
            temp = result.poly.erase(temp);
        temp++;
    }
    return result;
}

/**
 * @brief Overloaded equality comparison operator for Polynomial objects.
 * @param other The Polynomial object to compare to.
 * @return True if the Polynomials are equal, false otherwise.
 */
template <typename T>
bool Polynomial<T>::operator==(const Polynomial<T> &other) const
{
    if (this->poly.size() == other.poly.size())
    {
        auto it = this->poly.begin();
        auto io = other.poly.begin();
        while (it != this->poly.end() && io != other.poly.end())
        {
            if (it->deg() != io->deg() || (it->k()).getValue() != (io->k()).getValue())
                return false;
            it++;
            io++;
        }
        return true;
    }
    return false;
}

/*
 * @brief Overloaded inequality comparison operator for Polynomial objects.
 * @param other The Polynomial object to compare to.
 * @return True if the Polynomials are not equal, false otherwise.
 */

template <typename T>
bool Polynomial<T>::empty()
{
    if (poly.size > 0)
        return false;
    else
        return true;
}

/**
 * @brief Copies polynomшial
 * @param
 * @return Polynom copy
 */
template <typename T>
Polynomial<T>
Polynomial<T>::copy() const
{
    Polynomial<T> newPol(this->getNumMod());
    for (auto it = this->begin(); it != this->end(); ++it)
        newPol.addNode(Node<T>(it->k(), it->deg()));

    return newPol;
}

/**
 * @brief Gets coefficient of monomial
 * @param power Power of monomial
 * @return coefficient of monomial
 */
template <typename T>
modNum<T>
Polynomial<T>::getCoeff(const size_t power)
{
    if (power < 0 || power > this->getDegree())
        throw std::out_of_range("Index out of range");

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        if (power == it->deg())
            return it->k();
    }

    return static_cast<T>(0);
}

/**
 * @brief Shifts the polynomial to the right
 * @param positions Number of positions
 * @return Right-shifted polynomial
 */
template <typename T>
Polynomial<T>
Polynomial<T>::shiftRight(int positions) const
{
    if (positions <= 0)
        return *this;
    int deg = this->getDegree();

    Polynomial<T> tmp = this->copy();

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        tmp.addNode(it->k().getValue(), it->deg() + positions);
        tmp.poly.remove(Node<T>(it->k(), it->deg()));
    }

    return tmp;
}

/**
 *
 * @brief Converts the Polynomial object to a vector of value-degree pairs.
 * @details The Polynomial object is converted to a vector of value-degree
 * @tparam T The type of values stored in the Polynomial.
 * @return A vector of value-degree pairs representing the Polynomial.
 */

template <typename T>
std::vector<std::pair<T, size_t>>
Polynomial<T>::toPolyVector()
{
    std::vector<std::pair<T, size_t>> resV;
    resV.reserve(poly.size());

    for (Node<T> nd : poly)
    {
        resV.push_back(make_pair(nd.k().getValue(), nd.deg()));
    }

    return resV;
}
#endif