#ifndef POLY_INVERSE
#define POLY_INVERSE

#include "../poly-field-math.h"

template <typename T>
PolynomialField<T>
PolynomialField<T>::inv() const
{
    T mod = this->numMod;
    Polynomial<T> polyMod = this->value;
    Polynomial<T> poly = this->MOD;

    Polynomial<T> dividend = this->MOD;

    Polynomial<T> divisor = this->value;

    Polynomial<T> h(mod);
    h.addNode(0, 0);

    Polynomial<T> h2(mod);
    h2.addNode(1, 0);

    Polynomial<T> nul(mod);
    nul.addNode(0, 0);

    while (!(divisor == nul))
    {
        std::pair<Polynomial<T>, Polynomial<T>> quot = dividend.divClassic(divisor);
        Polynomial<T> quotient = quot.first;
        Polynomial<T> dividendcopy = dividend;
        dividend = divisor;
        divisor = dividendcopy - (quotient * divisor);

        Polynomial<T> copyh = h;
        h = h2;
        h2 = copyh - (quotient * h2);
    }

    Polynomial<T> res(mod);
    res.addNode(1, 0);

    PolynomialField result(mod, polyMod, (res / dividend) * h);
    return result;
}
template <typename T>
PolynomialField<T>
PolynomialField<T>::operator/(const PolynomialField<T> &other) const
{

    return (*this * (other.inv()));
}

#endif
