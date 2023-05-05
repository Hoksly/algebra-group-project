#include <list>
#include <iostream>

#ifndef POLY_NODE_H
#define POLY_NODE_H

#include <stdexcept>

template <typename T>
class Node
{
private:
    size_t degree;
    T koef;

public:
    Node();
    Node(T koef, size_t degree);
    ~Node() = default;

    size_t deg() const;
    T k() const;

    bool operator>(const Node<T>& p2) const;
    bool operator>=(const Node<T>& p2) const;
    bool operator<(const Node<T>& p2) const;
    bool operator<=(const Node<T>& p2) const;

    bool operator!=(const Node<T>& p2) const;
    Node<T> operator+(const Node<T>& p2) const;
    Node<T> operator-(const Node<T>& p2) const;
    void operator=(const Node<T>& p2);
    bool operator==(const Node<T>& p2) const;

    T evaluate() const;
};
#endif // POLY_NODE_H

#ifndef POLY_NODE_IMPLEMENTATION
#define POLY_NODE_IMPLEMENTATION

template <typename T>
Node<T>::Node() : degree(0), koef(0)
{
    degree = 0;
    koef = 0;
}

template <typename T>
Node<T>::Node(T koef, size_t degree) : degree(degree), koef(koef)
{
}

template <typename T>
bool Node<T>::operator>(const Node<T>& p2) const
{
    return degree > p2.degree;
}

template <typename T>
bool Node<T>::operator>=(const Node<T>& p2) const
{
    return degree >= p2.degree;
}

template <typename T>
bool Node<T>::operator<(const Node<T>& p2) const
{
    return degree < p2.degree;
}

template <typename T>
bool Node<T>::operator<=(const Node<T>& p2) const
{
    return degree <= p2.degree;
}

template <typename T>
bool Node<T>::operator==(const Node<T>& p2) const
{
    return degree == p2.degree;
}

template <typename T>
bool Node<T>::operator!=(const Node<T>& p2) const
{
    return degree != p2.degree;
}

template <typename T>
Node<T> Node<T>::operator+(const Node<T>& p2) const
{
    if (degree != p2.degree)
        throw std::logic_error("Can't add monomials with different powers");
    else
    {
        Node<T> res(koef + p2.koef, degree);
        return res;
    }
}

template <typename T>
Node<T> Node<T>::operator-(const Node<T>& p2) const
{
    if (degree != p2.degree)
        throw std::logic_error("Can't subtract monomials with different powers");
    else
    {
        Node<T> res(koef - p2.koef, degree);
        return res;
    }
}

template <typename T>
void Node<T>::operator=(const Node<T>& p2)
{
    degree = p2.degree;
    koef = p2.koef;
}

template <typename T>
size_t Node<T>::deg() const
{
    return degree;
}

template <typename T>
T Node<T>::k() const
{
    return koef;
}
#endif
