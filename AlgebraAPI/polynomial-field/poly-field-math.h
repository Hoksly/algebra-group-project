#ifndef POLY_FIELD
#define POLY_FIELD

#include "../polynomial-ring/poly-ring-math.h"

using namespace modular;

template <typename T>
bool isPrimeSimpleFunction(T num)
{
    T check = sqrt(num);

    for (int i = 2; i <= check; i++)
        if (num % i == 0)
            return false;
    return true;
}

template <typename T>
typename std::vector<T> nodes;

template <typename T>
class PolynomialField
{
protected:
    T numMod;

    Polynomial<T> value;
    Polynomial<T> MOD;

    void correct();

public:
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

    PolynomialField() = default;

    PolynomialField<T> operator+(const PolynomialField<T> &) const;
    PolynomialField<T> operator-(const PolynomialField<T> &) const;
    PolynomialField<T> operator*(const PolynomialField<T> &) const;
    PolynomialField<T> operator*(T num) const;

    bool operator==(const PolynomialField<T> &) const;
    PolynomialField<T> pow(T k);

    void addNode(const T num, size_t deg);
    void addNode(Node<T>);
    Polynomial<T> getValue() { return this->value; }

    static std::vector<PolynomialField<T>> cyclotomicToMultipliers(T num, T mod);

    static std::vector<PolynomialField<T>> findKIrreducible(size_t k);

    bool isIrreducible();

    void normalize();

    PolynomialField<T> inv() const;
    PolynomialField<T> operator/(const PolynomialField<T> &) const;

    size_t getOrder();

    bool isGenerator();

    void print() { value.print(); }
};

#include "source//poly-field-basic.tcc"
// #include "source//cyclotomicToMultipliers.tcc" -> lots of bugs so have to comment
#include "source/irredicibilityTest.tcc"
#include "source/inverse-poly.tcc"

#endif