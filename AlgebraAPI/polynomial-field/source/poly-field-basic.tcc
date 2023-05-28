#ifndef POLY_FIELD_BASICS_IMPLEMENTATION
#define POLY_FIELD_BASICS_IMPLEMENTATION

#include <cmath>

#include "../poly-field-math.h"

using namespace modular;

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator+(const PolynomialField<T> &other) const
{
    // Polynomial<T> p1 = this->value + other.value;
    // p1.print();
    // Polynomial<T> p2 = p1 % MOD;
    // MOD.print();
    // PolynomialField<T> res(numMod, MOD, p2);
    // return res;

    PolynomialField<T> res(numMod, MOD, (this->value + other.value) % MOD);
    return res;
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator-(const PolynomialField<T> &other) const
{
    PolynomialField<T> res(numMod, MOD, (this->value - other.value) % MOD);
    return res;
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator*(T num) const
{
    auto it = this->poly.begin();

    modNum<T> num1(num, this->numMod);

    while (it != this->poly.end())
    {
        it->k = it->k().getValue() * num1;
        it++;
    }
    return *this;
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator*(const PolynomialField<T> &other) const
{
    PolynomialField<T> res(numMod, MOD, (this->value * other.value) % MOD);
    return res;
}

template <typename T>
bool PolynomialField<T>::operator==(const PolynomialField<T> &other) const
{
    if (!(this->MOD == other.MOD))
    {
        return false;
    }
    return this->value == other.value;
}

template <typename T>
void 
PolynomialField<T>::addNode(Node<T> toAdd){
    value.addNode(toAdd);
    correct();
}

template <typename T>
void
PolynomialField<T>::correct(){
    value = value%MOD;
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::pow(T power)
{
    PolynomialField<T> valcp(this->numMod, this->MOD, this->value);

    PolynomialField<T> res(this->numMod, this->MOD, {{1, 0}});
    while (power)
    {
        if (power % 2 == 1)
            res = res * valcp;

        valcp = valcp * valcp;
        power /= 2;
    }
    res.value = res.value % MOD;
    return res;
}

#endif