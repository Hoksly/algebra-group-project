#ifndef POLY_NODE_IMPLEMENTATION
#define POLY_NODE_IMPLEMENTATION

#include <iostream>
#include <list>

#include "../poly-ring-math.h"

using namespace modular;

#include <stdexcept>

template <typename T>
Node<T>::Node() : degree(0), koef(0) {}

template <typename T>
Node<T>::Node(modular::modNum<T> koef, size_t degree) : degree(degree), koef(koef) {}

template <typename T>
bool
Node<T>::operator>(const Node<T> &p2) const {
    return degree > p2.degree;
}

template <typename T>
bool
Node<T>::operator>=(const Node<T> &p2) const {
    return degree >= p2.degree;
}

template <typename T>
bool
Node<T>::operator<(const Node<T> &p2) const {
    return degree < p2.degree;
}

template <typename T>
bool
Node<T>::operator<=(const Node<T> &p2) const {
    return degree <= p2.degree;
}

template <typename T>
bool
Node<T>::operator==(const Node<T> &p2) const {
    return degree == p2.degree && koef == p2.koef;
}

template <typename T>
bool
Node<T>::operator!=(const Node<T> &p2) const {
    return degree != p2.degree && koef != p2.koef;
}

template <typename T>
Node<T>
Node<T>::operator+(const Node<T> &p2) const {
    if (degree != p2.degree)
        throw std::logic_error("Can't add monomials with different powers");
    else {
        Node<T> res(koef + p2.koef, degree);
        return res;
    }
}

template <typename T>
Node<T>
Node<T>::operator-(const Node<T> &p2) const {
    if (degree != p2.degree)
        throw std::logic_error("Can't subtract monomials with different powers");
    else {
        Node<T> res(koef - p2.koef, degree);
        return res;
    }
}

template <typename T>
void
Node<T>::operator=(const Node<T> &p2) {
    degree = p2.degree;
    koef = p2.koef;
}

template <typename T>
size_t
Node<T>::deg() const {
    return degree;
}

template <typename T>
modNum<T>
Node<T>::k() const {
    return koef;
}
template <typename T>
modNum<T>
Node<T>::evaluate(T xVal) const {
    modNum<T> res(xVal, koef.getMod());
    res = fpow(res, degree);
    res = res * koef;
    return res;
}
#endif