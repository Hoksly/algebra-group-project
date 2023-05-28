#ifndef POLY_DIV_AND_GCD
#define POLY_DIV_AND_GCD

#include "../poly-ring-math.h"

/**
 * @brief Polynomial long division
 * @param other Divisor(polynomial)
 * @return std::pair of quotient and remainder
 */
template <typename T>
std::pair<Polynomial<T>, Polynomial<T>>

Polynomial<T>::divClassic(const Polynomial<T> &other) const
{
    int numDeg = this->getDegree();
    int denomDeg = other.getDegree();

    if (other.poly.empty())
        throw std::invalid_argument("Divisor must have at least one non-zero coefficient");
    else if (this->getNumMod() != other.getNumMod())
        throw std::invalid_argument("Can't add Polynomials with diferent modulas");
    else if (numDeg < denomDeg)
    {
        // throw std::invalid_argument(
        //     "The degree of the divisor cannot exceed that of the numerator");

        Polynomial<T> remainder = this->copy();
        Polynomial<T> quotient(11);

        return std::make_pair(quotient, remainder);
    }

    else if (denomDeg == 0)
    {
        modNum<T> numb(other.poly.begin()->k().getValue(), other.getNumMod());
        return this->divClassic(numb);
    }
    else
    {
        Polynomial<T> remainder = this->copy();
        Polynomial<T> quotient(this->getNumMod());

        while (numDeg >= denomDeg)
        {
            Polynomial<T> denomTmp = other.shiftRight(numDeg - denomDeg);
            auto val = remainder.getCoeff(numDeg) / denomTmp.getCoeff(numDeg);
            quotient.addNode(val.getValue(), numDeg - denomDeg);
            Polynomial<T> num(quotient.getNumMod());
            num.addNode(quotient.getCoeff(numDeg - denomDeg).getValue(), 0);

            denomTmp = denomTmp * num;

            remainder = remainder - denomTmp;

            numDeg = remainder.getDegree();
        }

        return std::make_pair(quotient, remainder);
    }
}

/**
 * @brief Polynomial division by number
 * @param other divisor(modNum)
 * @return std::pair of quotient and remainder
 */

template <typename T>
std::pair<Polynomial<T>, Polynomial<T>>
Polynomial<T>::divClassic(const modNum<T> &other) const
{
    Polynomial<T> remainder(this->getNumMod());
    Polynomial<T> quotient(this->getNumMod());

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        auto val3 = it->k() / other;
        quotient.addNode(val3.getValue(), it->deg());
    }

    return std::make_pair(quotient, remainder);
}
/*
 * @brief Polynomial division by number
 * @param other divisor(modNum)
 * @return std::pair of quotient and remainder
 */

template <typename T>
Polynomial<T>
Polynomial<T>::operator/(const Polynomial<T> &other) const
{
    return this->divClassic(other).first;
}

/*
 * @brief Polynomial division by number
 * @param other divisor(modNum)
 * @return std::pair of quotient and remainder
 */
template <typename T>
Polynomial<T>
Polynomial<T>::operator%(const Polynomial<T> &other) const
{
    return this->divClassic(other).second;
}

/*
 * @brief Polynomial division by number
 * @param other divisor(modNum)
 * @return std::pair of quotient and remainder
 */
template <typename T>
Polynomial<T>
Polynomial<T>::operator/(const modNum<T> &other) const
{
    return this->divClassic(other).first;
}

/*
 * @brief Polynomial division by number
 * @param other divisor(modNum)
 * @return std::pair of quotient and remainder
 */
template <typename T>
Polynomial<T>
Polynomial<T>::operator%(const modNum<T> &other) const
{
    return this->divClassic(other).second;
}

/**
 * @brief Polynomials Greatest Common Divisor
 * @param other Other polynomial
 * @return GCD polynomial
 */
template <typename T>
Polynomial<T>
Polynomial<T>::gcd(const Polynomial<T> &other) const
{
    Polynomial<T> g = this->copy(), h = other.copy();

    while (!h.poly.empty())
    {
        auto divRes = g.divClassic(h);
        g = h;
        h = divRes.second;
    }

    if (!g.poly.empty() && g.poly.front().k().getValue() > 1)
    {
        modNum<T> numb(g.poly.begin()->k().getValue(), g.getNumMod());

        auto res = g.divClassic(numb);
        g = res.first;
    }

    return g;
}

#endif