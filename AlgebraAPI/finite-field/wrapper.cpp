#include "mod-math.h"
#include "source/custom-hash.h"

#include <gmpxx.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string.h>

using namespace modular;
const size_t MESSAGE_LEN = 200;

/**
 *
 *    @brief Adds two numbers and returns their sum modulo a given number.
 *    @param a The first number to be added.
 *    @param b The second number to be added.
 *    @param mod The number to take the result modulo with.
 *    @return A char pointer to the result of the subtraction in string form
 *    @note memory should be manualy freed by delete[]
 *    */
extern "C" char *
addition(char *a, char *b, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numB, numMod;
        numA.set_str(a, 10), numB.set_str(b, 10), numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod), b1(numB, numMod), res;
        res = a1 + b1;

        char *resStr = new char[MESSAGE_LEN];
        strcpy(resStr, res.getValue().get_str().c_str());
        return resStr;
    }
    catch (const std::exception &ex)
    {
        strcpy(errorStr, ex.what());
    }

    return resStr;
}

/**
 *
 *    @brief Subtracts two numbers a and b modulo mod
 *    @param a The minuend (
 *    @param b The subtrahend
 *    @param mod The modulus of the operation
 *    @return A char pointer to the result of the subtraction in string form
 *    @note memory should be manualy freed by delete[]
 *    */
extern "C" char *
subtraction(char *a, char *b, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numB, numMod;
        numA.set_str(a, 10), numB.set_str(b, 10), numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod), b1(numB, numMod), res;

        res = a1 - b1;

        char *resStr = new char[MESSAGE_LEN];
        strcpy(resStr, res.getValue().get_str().c_str());
        return resStr;
    }
    catch (const std::exception &ex)
    {
        strcpy(errorStr, ex.what());
    }

    return resStr;
}

/**
 *
 *    @brief Multiply two numbers modulo mod
 *    @param a The first number in string form
 *    @param b The second number in string form
 *    @param mod The number to take the modulus by in string form
 *    @return A char pointer to the result of the multiplication in string form
 *    @note memory should be manualy freed by delete[]
 */
extern "C" char *
multiplication(char *a, char *b, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numB, numMod;

        numA.set_str(a, 10), numB.set_str(b, 10), numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod), b1(numB, numMod), res;

        res = a1 * b1;

        char *resStr = new char[MESSAGE_LEN];
        strcpy(resStr, res.getValue().get_str().c_str());
        return resStr;
    }
    catch (const std::exception &ex)
    {
        strcpy(errorStr, ex.what());
    }

    return resStr;
}

/**
 *
 *    @brief Performs modular division of two large integers.
 *    @param a string representing the numerator.
 *    @param b  string representing the denominator.
 *    @param mod  string representing the modulus.
 *    @return A char pointer to the result of modular division.
 *    @note memory should be manualy freed by delete[]
 */
extern "C" char *
division(char *a, char *b, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numB, numMod;
        numA.set_str(a, 10), numB.set_str(b, 10), numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod), b1(numB, numMod), res;

        res = a1 / b1;

        char *resStr = new char[MESSAGE_LEN];
        strcpy(resStr, res.getValue().get_str().c_str());
        return resStr;
    }
    catch (const std::exception &ex)
    {
        strcpy(errorStr, ex.what());
    }
    return resStr;
}
extern "C" char *
fastPow(char *a, char *degree, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numDegree, numMod;
        numA.set_str(a, 10), numDegree.set_str(degree, 10), numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod), res;

        res = fpow(a1, numDegree);
        char *resStr = new char[MESSAGE_LEN];
        strcpy(resStr, res.getValue().get_str().c_str());
        return resStr;
    }
    catch (const std::exception &ex)
    {
        strcpy(errorStr, ex.what());
    }

    return resStr;
}
extern "C" char *
inverse(char *num, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numMod;
        numA.set_str(num, 10), numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod), res;

        res = a1.inv();
        char *resStr = new char[MESSAGE_LEN];
        strcpy(resStr, res.getValue().get_str().c_str());
        return resStr;
    }
    catch (const std::exception &ex)
    {
        strcpy(errorStr, ex.what());
    }

    return resStr;
}

/**
 *
 *    @brief Factorize a number modulo a given modulus.
 *    This function computes the prime factorization of a number modulo a given modulus.
 *    @param size Reference to a variable that will hold the number of prime factors found.
 *    @param num The number to factorize.
 *    @param mod The modulus.
 *    @return An array of strings representing the prime factors. The first element of the array is
 * the number of factors.
 *    @throw std::length_error if the number of prime factors is greater than 127.
 *    */
extern "C" char *
factorizePolard(size_t &size, char *num, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numMod;
        numA.set_str(num, 10);
        numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod);

        std::vector<modNum<mpz_class>> res = modular::factorize(a1);

        std::string strCombined;

        for (modNum<mpz_class> num : res)
        {
            strCombined += num.getValue().get_str();
            strCombined += " ";
        }

        char *resStr = new char[strCombined.size() + 1];
        strcpy(resStr, strCombined.c_str());
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
    }

    return resStr;
}

/**
 * @brief Factorizes a given number modulo another number using the naive factorization algorithm.
 * This function takes two input numbers and factorizes the first number modulo the second number
 * using the naive factorization algorithm, implemented using the modNum template class and the GMP.
 * The factorized numbers are returned as a dynamically allocated 2D char array, where each row of
 * the array represents a factor in string format. The total number of factors is returned in the
 * input parameter 'size'. In case of any runtime errors, the function throws an exception, and the
 * error message is stored in the input parameter 'errorStr'.
 *
 * @param size A reference to a variable to store the total number of factors obtained.
 * @param num The number to be factorized in string format.
 * @param mod The number to take the input number modulo with in string format.
 * @param errorStr A char pointer to store the error message in case of exception.
 * @return A dynamically allocated 2D char array storing the factors obtained in string format.
 * @note The memory for the result array should be manually freed by the user using 'delete[]'.
 */
extern "C" char *
factorizeSimple(size_t &size, char *num, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numMod;
        numA.set_str(num, 10);
        numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod);

        std::vector<modNum<mpz_class>> res = modular::naiveFactorize(a1);

        std::string strCombined;

        for (modNum<mpz_class> num : res)
        {
            strCombined += num.getValue().get_str();
            strCombined += " ";
        }

        char *resStr = new char[strCombined.size() + 1];
        strcpy(resStr, strCombined.c_str());
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
    }

    return resStr;
}
/**
 *
 *    @brief Calculate the discrete square root of a given number modulo a given modulus
 *    @param num the number to take the square root of
 *    @param mod the modulus to calculate the square root modulo
 *    @return A string representation of the discrete square root of the given number modulo the
 * given modulus
 *    */

extern "C" char *
discreteSqrt(size_t &retSize, char *num, char *mod, char *errorStr)
{
    try
    {
        mpz_class numA, numMod;

        numA.set_str(num, 10);

        numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod);
        std::vector<mpz_class> res;

        res = modular::sqrt(a1);

        std::string strCombined;

        for (mpz_class num : res)
        {
            strCombined += num.get_str();
            strCombined += " ";
        }

        char *resStr = new char[strCombined.size() + 1];
        strcpy(resStr, strCombined.c_str());

        return resStr;
    }
    catch (const std::exception &ex)
    {
        strcpy(errorStr, ex.what());
        return nullptr;
    }
}

/**
 *
 *    @brief Computes the discrete logarithm of a number to a given base modulo a given modulus
 *    Computes the smallest integer 'x' such that (base ^ x) % mod == num.
 *    @param num the number whose logarithm is to be found
 *    @param base the base of the logarithm
 *    @param mod the modulus used in the computation
 *    @return a string representation of the computed logarithm
 *    */
extern "C" char *
discreteLog(char *num, char *base, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numB, numMod;

        numA.set_str(num, 10);
        numB.set_str(base, 10);

        numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod), b1(numB, numMod);

        mpz_class res;

        res = modular::log(a1, b1);
        resStr = new char[MESSAGE_LEN];
        strcpy(resStr, res.get_str().c_str());
    }
    catch (const std::exception &ex)
    {
        strcpy(errorStr, ex.what());
    }

    return resStr;
}

// /**
//  *
//  *   @brief Calculates the order of an element in a finite field.
//  *   Given an integer number 'num' and a modulus 'mod', calculates the smallest positive
//  *   integer 'k' such that num^k = 1 (mod mod). The function returns the order 'k' as a string.
//  *  @param num base number
//  *  @param mod modulus
//  *  @return string representation of the order of the element
//  */
// extern "C" char *
// orderOfElement(char *num, char *mod, char *errorStr)
// {
//     char *resStr = nullptr;
//     try
//     {
//         mpz_class numA, numMod, res;

//         numA.set_str(num, 10);

//         numMod.set_str(mod, 10);

//         modNum<mpz_class> a1(numA, numMod);

//         res = modular::orderOfElement(a1);

//         resStr = new char[MESSAGE_LEN];
//         strcpy(resStr, res.get_str().c_str());
//     }
//     catch (const std::exception &e)
//     {
//         strcpy(errorStr, e.what());
//     }

//     return resStr;
// }

/**
 *
 *    @brief Checks if a given number is a group generator
 *    @param num the number to check if it is a generator
 *    @param mod the modulus
 *    @return true if num is a generator, false otherwise
 *    */
extern "C" bool
isGenerator(char *num, char *mod, char *errorStr)
{
    try
    {
        char *resStr = nullptr;
        mpz_class numA, numMod, res;

        numA.set_str(num, 10);

        numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod);

        return modular::isGenerator(a1);
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
    }
    return false;
}

/**
 *
 *    @brief Calculates Euler's totient function of a given number modulo m.
 *    @param num A string representation of the number for which Euler's totient function is to be
 * calculated.
 *    @param mod A string representation of the modulo for the calculation of Euler's totient
 * function.
 *    @return A string representation of the value of Euler's totient function of the given number
 * modulo m.
 *    */

extern "C" char *
EulerFunction(char *num, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numMod;
        numA.set_str(num, 10), numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod), res;

        res = modular::eulerFunction(a1);

        resStr = new char[MESSAGE_LEN];
        strcpy(resStr, res.getValue().get_str().c_str());
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
    }

    return resStr;
}

/**
 *
 *    @brief Calculates the Carmichael Function λ(n) for a given number n and modulus mod
 *    @param num the number for which to calculate the Carmichael Function
 *    @param mod the modulus used to calculate the Carmichael Function
 *   @return The value of the Carmichael Function as a string
 *
 */

extern "C" char *
CarmichaelFunction(char *num, char *mod, char *errorStr)
{
    char *resStr = nullptr;
    try
    {
        mpz_class numA, numMod;

        numA.set_str(num, 10);

        numMod.set_str(mod, 10);

        modNum<mpz_class> a1(numA, numMod);
        mpz_class res;

        res = modular::CarmichaelFunction(numA);

        resStr = new char[MESSAGE_LEN];
        strcpy(resStr, res.get_str().c_str());
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
    }

    return resStr;
}

/**
 *
 *    @brief Determines if a given number is prime using the Miller-Rabin primality test
 *    @param num A char pointer to the number being checked for primality
 *    @param mod A char pointer to the modulus used to perform the modular arithmetic
 *    @param iterations A char pointer to the number of iterations used to perform the
 * Miller-Rabin test
 *    @return A boolean value indicating whether the given number is prime (true) or not (false)
 *   */

extern "C" bool
isPrime(char *num, char *mod, char *iterations, char *errorStr)
{
    try
    {
        mpz_class numA, numMod, res;

        numA.set_str(num, 10);

        numMod.set_str(mod, 10);
        size_t iters = atoll(iterations);

        modNum<mpz_class> a1(numA, numMod);

        return modular::isPrime(a1, iters);
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
    }

    return false;
}

int main()
{
}

// Compile: g++ wrapper.cpp -lgmpxx -lgmp

/*

em++ -O3 -s MODULARIZE=1 -s "EXPORT_NAME='testModule'" -s  -s "EXPORTED_FUNCTIONS=['_addition']" \
-o myModule.wasm wrapper.cpp  -I/usr/include

em++ -o test.js test.cpp "EXPORTED_FUNCTIONS=['_addition']" -s EXPORT_NAME='testModule'" -s
MODULARIZE=1 -L/${HOME}/opt/lib/libgmp.a -I${HOME}/opt/include

*/