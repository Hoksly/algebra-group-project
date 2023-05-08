#include <climits>
#include <list>
#include <vector>
#include <iostream>
#include "node.tcc"

using namespace modular;

#ifndef POLYNOMIAL
#define POLYNOMIAL

template <typename T>
class Polynomial
{
private:
    std::list<Node<T>> poly;
    size_t degree = 0;
    T numMod = 0;

    ///////////////////////Irreducable test///////////////////////////////////////////////////////
    bool PerronTest();
    bool CohnTest();
    bool RootTest();
    bool isPrime(T num); // crutial part for some test; any ideas for better algorithm are welcomed
    long long findPower(int i, int deg);
    /////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////For polynomial long division//////////////////////////////////////////
    modNum<T> getCoeff(const size_t power);
    Polynomial<T> copy() const;
    Polynomial<T> shiftRight(int positions) const;
    /////////////////////////////////////////////////////////////////////////////////////////////

public:
    Polynomial(T mod) : numMod(mod){};
    Polynomial(std::vector<std::pair<T, size_t>>, T);
    Polynomial(std::pair<T, size_t> *arr, size_t n, T);

    ~Polynomial() = default;

    Node<T> operator[](const size_t i); // use only when really necessary

    bool empty();
    typename std::list<Node<T>>::const_iterator begin() const { return poly.begin(); };
    typename std::list<Node<T>>::const_iterator end() const { return poly.end(); };

    void addNode(const Node<T>);
    void addNode(const T, size_t);

    void removeNode(const Node<T>); // by value
    void removeNode(const size_t);  // by degree

    size_t getDegree() const
    {
        if (poly.empty())
            return INT_MIN;
        else
            return degree;
    };
    T getNumMod() const { return numMod; }

    void print() const;

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> operator+(const Polynomial<T> &) const;
    Polynomial<T> operator-(const Polynomial<T> &) const;
    Polynomial<T> operator*(const Polynomial<T> &) const;
    bool operator==(const Polynomial<T> &) const;

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> der() const; // deriveative
    modNum<T> evaluate(const T) const;
    modNum<T> evaluate(const modNum<T>) const;

    //////////////////////////////////////////////////////////////////////////////

    std::pair<Polynomial<T>, Polynomial<T>> operator/(const Polynomial<T> &) const;

    Polynomial<T> gcd(const Polynomial<T> &) const;

    //////////////////////////////////////////////////////////////////////////////

    static Polynomial<T> getPolynomialByOrder(size_t);

    bool isIrreducable() const;
};

#endif

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

    throw std::out_of_range("Index out of range");
}

template <typename T>
std::ostream &operator<<(std::ostream &os, Node<T> &p)
{
    return os << '{' << p.deg() << ", " << p.k().getValue() << '}';
}

template <typename T>
Polynomial<T> Polynomial<T>::der() const
{
    Polynomial<T> returned_field;
    Node<T> current_newnode;
    T new_koef;
    T new_pow;

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        new_koef = it->k() * it->deg();
        new_pow = it->deg() - 1;
        if (new_pow < 1)
        {
            new_koef = 0;
            new_pow = 0;
        }
        current_newnode = {new_pow, new_koef};
        returned_field.addNode(current_newnode);
    }

    return returned_field;
}

template <typename T>
modNum<T> Polynomial<T>::evaluate(const T x_value) const
{

    modNum<T> sum(0, numMod);
    modNum<T> current_num(0, numMod);

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        if (it->deg() > 0)
        {
            current_num = fpow(modNum<T>(x_value, numMod), it->deg()) * it->k();
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
modNum<T> Polynomial<T>::evaluate(const modNum<T> x_value) const
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

template <typename T>
void Polynomial<T>::addNode(const T num, size_t deg)
{
    if (num % numMod)
    {
        Node<T> a(modNum(num % numMod, numMod), deg);
        this->addNode(a);
    }
}

template <typename T>
Polynomial<T>::Polynomial(std::vector<std::pair<T, size_t>>, T mod) : Polynomial(mod)
{
}

/**
 * @brief Adds two polynomials.
 * @param other The polynomial to add to the current polynomial.
 * @return Polynomial<T> The result of adding two polynomials.
 */
template <typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T> &other) const
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
            modNum<T> temp = t + (modNum<T>(0));
            result.addNode(temp.getValue(), it->deg());
            it++;
        }
        else
        {
            modNum<T> t = io->k();
            modNum<T> temp = t + (modNum<T>(0));
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
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T> &other) const
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
Polynomial<T> Polynomial<T>::operator*(const Polynomial<T> &other) const
{
    if (this->getNumMod() != other.getNumMod())
    {
        throw std::invalid_argument("Can't add Polynomials with diferent modulas");
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

template <typename T>
bool Polynomial<T>::empty()
{
    if (poly.size > 0)
        return false;
    else
        return true;
}

template <typename T>
bool Polynomial<T>::isIrreducable() const
{
    auto k = poly.end();
    k--;
    Node<T> first = *poly.begin();
    Node<T> last = *k;
    if (first.deg() == 1)
        return true;
    if (last.deg() != 0)
        return false;
    if (first.k() == 1 && PerronTest())
        return true;
    if (CohnTest())
        return true;
    if (RootTest())
        return false;
    return true;
}

template <typename T>
bool Polynomial<T>::RootTest()
{
    for (int i = 1; i < numMod; i++)
    {
        T sum = 0;
        for (auto j = poly.begin(); j != poly.end(); j++)
        {
            Node<T> temp = *j;
            long long power = findPower(i, temp.deg());
            sum = (sum + temp.k() * power) % numMod;
        }

        if (sum == 0)
            return true;
    }
    return false;
}

template <typename T>
long long Polynomial<T>::findPower(int i, int deg)
{
    long long power = 1;
    for (int j = 1; j <= deg; j++)
    {
        power = (power * i) % numMod;
    }

    return power;
}

template <typename T>
bool Polynomial<T>::PerronTest()
{
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

    if (second.k() > sum)
        return true;
    else
        return false;
}

template <typename T>
bool Polynomial<T>::CohnTest()
{
    T sum = 0;

    auto k = poly.begin();
    Node<T> temp = *(k);
    for (int i = temp.deg(); i > -1; i--)
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
bool Polynomial<T>::isPrime(T num)
{
    T check = sqrt(num);

    for (int i = 2; i <= check; i++)
        if (num % i == 0)
            return false;
    return true;
}

/**
 * @brief Copies polynomшial
 * @param
 * @return Polynom copy
 */
template <typename T>
Polynomial<T> Polynomial<T>::copy() const
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
modNum<T> Polynomial<T>::getCoeff(const size_t power)
{
    if (power < 0 || power > this->getDegree())
        throw std::out_of_range("Index out of range");

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        if (power == it->deg())
            return it->k();
    }

    throw std::out_of_range("Index out of range");
}

/**
 * @brief Shifts the polynomial to the right
 * @param positions Number of positions
 * @return Right-shifted polynomial
 */
template <typename T>
Polynomial<T> Polynomial<T>::shiftRight(int positions) const
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
 * @brief Polynomial long division
 * @param other Divisor
 * @return std::pair of quotient and remainder
 */
template <typename T>
std::pair<Polynomial<T>, Polynomial<T>> Polynomial<T>::operator/(const Polynomial<T> &other) const
{
    int numDeg = this->getDegree();
    int denomDeg = other.getDegree();

    if (other.poly.empty())
        throw std::invalid_argument("Divisor must have at least one non-zero coefficient");
    else if (this->getNumMod() != other.getNumMod())
        throw std::invalid_argument("Can't add Polynomials with diferent modulas");
    else if (numDeg < denomDeg)
        throw std::invalid_argument("The degree of the divisor cannot exceed that of the numerator");
    else if (denomDeg == 0)
    {
        Polynomial<T> remainder(this->getNumMod());
        Polynomial<T> quotient(this->getNumMod());
        modNum<T> val = other.poly.begin()->k();

        for (auto it = poly.begin(); it != poly.end(); ++it)
        {
            modNum<T> val2 = it->k();
            auto val3 = val2 / val;
            quotient.addNode(val3.getValue(), it->deg()); // modnum
        }

        return std::make_pair(quotient, remainder);
    }
    else
    {
        Polynomial<T> remainder = this->copy();
        Polynomial<T> quotient(this->getNumMod());

        while (numDeg >= denomDeg)
        {
            Polynomial<T> denomTmp = other.shiftRight(numDeg - denomDeg);
            // std::cout << "denomTmp  "; denomTmp.print();
            auto x1 = remainder.getCoeff(numDeg);
            auto x2 = denomTmp.getCoeff(numDeg);
            auto x = x1 / x2;
            quotient.addNode(x.getValue(), numDeg - denomDeg);
            // std::cout << "quotient  ";quotient.print();

            Polynomial<T> num(quotient.getNumMod());
            num.addNode(quotient.getCoeff(numDeg - denomDeg).getValue(), 0);

            denomTmp = denomTmp * num;
            // std::cout << "remainder  ";remainder.print();
            //  std::cout << "denomTmp  "; denomTmp.print();
            remainder = remainder - denomTmp;
            // std::cout << "remainder  ";remainder.print();
            numDeg = remainder.getDegree();
        }

        return std::make_pair(quotient, remainder);
    }
}
/**
 * @brief Polynomials Greatest Common Divisor
 * @param other Other polynomial
 * @return GCD polynomial
 */
template <typename T>
Polynomial<T> Polynomial<T>::gcd(const Polynomial<T> &other) const
{
    Polynomial<T> g = this->copy(), h = other.copy();

    while (!h.poly.empty())
    {
        auto divRes = g / h;
        g = h;
        h = divRes.second;
    }

    if(!g.poly.empty() && g.poly.front().k() > 1){
        auto firstCoeff = g.poly.front().k();

        Polynomial<T> monic(g.numMod);
        for (auto it = g.poly.begin(); it != g.poly.end(); ++it){
            monic.addNode(Node<T>(it->k() / firstCoeff, it->deg()));
        }
        return monic;
    }

    return g;
}