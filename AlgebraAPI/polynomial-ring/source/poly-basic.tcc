#include <list>
#include <iostream>
#include "Node.h"


#ifndef POLYNOMIAL
#define POLYNOMIAL

template <typename T>
class Polynomial
{
private:
    std::list<Node<T>> poly;
    size_t degree;
    T numMod;
    
    ///////////////////////Irreducable test///////////////////////////////////////////////////////
    bool PerronTest();
    bool CohnTest();
    bool RootTest();
    bool isPrime(T num); //crutial part for some test; any ideas for better algorithm are welcomed
    long long findPower(int i, int deg);
    /////////////////////////////////////////////////////////////////////////////////////////////

public:
    Polynomial(T mod);

    ~Polynomial() = default;

    Node<T> operator[](const size_t i); // use only when really necessary

    bool empty();
    typename std::list<Node<T>>::const_iterator begin() const;
    typename std::list<Node<T>>::const_iterator end() const;

    void addNode(const Node<T>);

    void removeNode(const Node<T>); // by value
    void removeNode(const size_t);  // by degree

    size_t deg() const;
    T modulo() const;

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> operator+(const Polynomial<T>&) const;
    Polynomial<T> operator-(const Polynomial<T>&) const;
    Polynomial<T> operator*(const Polynomial<T>&) const;

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> der() const; // deriveative
    T evaluate() const;

    //////////////////////////////////////////////////////////////////////////////

    std::pair<Polynomial<T>, Polynomial<T>> operator/(const Polynomial<T>&) const;

    Polynomial<T> gcd(const Polynomial<T>&) const;

    //////////////////////////////////////////////////////////////////////////////

    static Polynomial<T> getPolynomialByOrder(size_t);
    
    bool isIrreducable();
};

#endif

template<typename T>
Polynomial<T>::Polynomial(T mod) {
    numMod = mod;
}

template <typename T>
T Polynomial<T>::modulo() const {
    return numMod;
}

template <typename T>
size_t Polynomial<T>::deg() const {
    return degree;
}

template <typename T>
void Polynomial<T>::addNode(const Node<T> p) {
    if (p.k() != 0) {
        T toAddCoef = p.k() % numMod;
        Node<T> newP(toAddCoef, p.deg());

        bool inserted = false;
        for (auto i = poly.begin(); i != poly.end(); i++)
        {
            Node<T> pl = (*i);
            if (newP.deg() > pl.deg()) {
                poly.insert(i, newP);
                inserted = true;
                break;
            }
        }
        if (!inserted)
            poly.push_back(newP);

        if (newP.deg() > degree) degree = newP.deg();
    }
}

template <typename T>
bool Polynomial<T>::empty() {
    if (poly.size > 0) return false;
    else
        return true;
}

template <typename T>
Node<T> Polynomial<T>::operator[](const size_t i)
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
}

template <typename T>
bool Polynomial<T>::isIrreducable() {
    auto k = poly.end();
    k--;
    Node<T> first = *poly.begin();
    Node<T> last = *k;
    if (first.deg() == 1) return true;
    if (last.deg() != 0) return false;
    if (first.k() == 1 && PerronTest()) return true;
    if (CohnTest()) return true;
    if (RootTest()) return false;
    return true;
}

template <typename T>
bool Polynomial<T>::RootTest() {
    for (int i = 1; i < numMod; i++)
    {
        T sum = 0;
        for (auto j = poly.begin(); j != poly.end(); j++)
        {
            Node<T> temp = *j;
            long long power = findPower(i, temp.deg());
            sum = (sum + temp.k() * power) % numMod;
        }

        if (sum == 0) return true;
    }
    return false;
}

template <typename T>
long long Polynomial<T>::findPower(int i, int deg) {
    long long power = 1;
    for (int j = 1; j <= deg; j++)
    {
        power = (power * i) % numMod;
    }

    return power;
}

template <typename T>
bool Polynomial<T>::PerronTest() {
    auto i = poly.begin();
    i++;
    Node<T> second = *(i);
    
    T sum = 0;
    i++;
    for (auto j = i; j != poly.end(); j++)
    {
        Node<T> temp = (*j);
        sum = sum + temp.k();
    }

    if (second.k() > sum) return true;
    else
        return false;
}

template <typename T>
bool Polynomial<T>::CohnTest() {
    T sum = 0;

    auto k = poly.begin();
    Node<T> temp = *(k);
    for (int i = temp.deg(); i>-1; i--)
    {
        temp = *k;
        if (i == temp.deg())
        {
            sum = sum + temp.k();
            k++;
        }
        sum = sum * 10;
    }
    sum = sum / 10;
    
    if (isPrime(sum))
        return true;
    else
        return false;
}

template <typename T>
bool Polynomial<T>::isPrime(T num) {
    T check = sqrt(num);

    for (int i = 2; i <= check; i++)
        if (num % i == 0)
            return false;
    return true;
}

// Function to print Node
template <typename T>
std::ostream& operator<<(std::ostream& os, Node<T>& p)
{
    return os << '{' << p.k() << ", " << p.deg() << '}';
}
