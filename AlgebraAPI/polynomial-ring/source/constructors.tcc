#include "poly-basic.tcc"

#ifndef ADDITIONAL_CONSTRUCTORS_TCC
#define ADDITIONAL_CONSTRUCTORS_TCC

template <class T>
bool cmp(const std::pair<T, size_t> &one, const std::pair<T, size_t> &two)
{
    return one.second < two.second;
}

/*
 * @brief Constructs a polynomial from a vector of values and a modulus.
 * @tparam T The type of values stored in the polynomial.
 * @param nodes A vector of values and their degrees.
 * @param mod The modulus of the polynomial.
 */
template <class T>
Polynomial<T>::Polynomial(std::vector<std::pair<T, size_t>> nodes, T mod)
{
    this->numMod = mod;

    for (auto valDegreePair : nodes)
    {
        this->addNode(valDegreePair.first, valDegreePair.second);
    }
}
#endif
