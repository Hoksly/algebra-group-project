#include "poly-ring-math.h"

#include <gmpxx.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

const size_t MESSAGE_LEN = 200;
/**
 * Converts a string representation of a polynomial to a vector of pairs.
 *
 * @param polyString   The string representation of the polynomial.
 * @param polySize     The size of the polynomial.
 * @param numMod       The modulus value.
 * @return             A vector of pairs representing the polynomial.
 */
vector<std::pair<mpz_class, size_t>>
stringToPolyVector(char **polyString, size_t polySize, mpz_class numMod)
{
    vector<std::pair<mpz_class, size_t>> polyV(polySize);

    for (size_t i = 0; i < polySize; ++i)
    {
        mpz_class a;
        a.set_str(polyString[i * 2], 10);

        std::string s(polyString[i * 2 + 1]);
        std::stringstream sstream(s);
        size_t b;
        sstream >> b;

        polyV[i] = make_pair(a, b);
    }

    return polyV;
}
/**
 * Converts a vector of pairs representing a polynomial to a string array.
 *
 * @param polyV   The vector of pairs representing the polynomial.
 * @return        A string array representation of the polynomial.
 */
char **
polyVectorToString(vector<std::pair<mpz_class, size_t>> polyV)
{
    char **resStr = new char *[polyV.size() * 2];

    for (size_t i = 0; i < polyV.size(); ++i)
    {
        resStr[i * 2] = new char[MESSAGE_LEN];
        strcpy(resStr[i * 2], polyV[i].first.get_str().c_str());

        resStr[i * 2 + 1] = new char[MESSAGE_LEN];
        strcpy(resStr[i * 2 + 1], std::to_string(polyV[i].second).c_str());
    }

    return resStr;
}
/**
 * Removes spaces from a given string.
 *
 * @param str   The input string.
 * @return      The string with spaces removed.
 */
std::string
removeSpaces(std::string str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}
/**
 * Replaces all occurrences of a substring in a string with another substring.
 *
 * @param str     The input string.
 * @param from    The substring to be replaced.
 * @param to      The substring to replace with.
 * @return        The modified string with replacements.
 */
std::string ReplaceAll(std::string str, const std::string &from, const std::string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
/**
 * Converts a polynomial string into a vector of pairs.
 *
 * @param polynomial   The string representation of the polynomial.
 * @return             A vector of pairs representing the polynomial.
 */
std::vector<std::pair<std::string, std::string>>
convertPolynomial(std::string polynomial)
{
    polynomial = removeSpaces(polynomial);
    std::vector<std::pair<std::string, std::string>> result;
    std::string newPol = ReplaceAll(polynomial, "-", " +-");
    std::stringstream ss(newPol);
    std::string term;

    while (std::getline(ss, term, '+'))
    {
        int32_t posX = term.find("x");
        std::string coeff, degree;
        int32_t posDeg = term.find("^");

        if (posX != -1)
        {
            coeff = term.substr(0, term.find("x"));
            if (coeff == "")
                coeff = "1";
            if (posDeg != -1)
                degree = term.substr(posDeg + 1, term.size() - 1);
            else
            {
                degree = "1";
            }
        }

        else
        {
            coeff = term;
            degree = "0";
        }
        result.push_back({coeff, degree});
    }
    return result;
}
/**
 * Parses a polynomial string and returns it as a string array.
 *
 * @param polySize     The size of the polynomial.
 * @param polyString   The string representation of the polynomial.
 * @return             A string array representation of the polynomial.
 */
extern "C" char **
polyParse(size_t &polySize, char *polyString)
{
    std::vector<std::pair<std::string, std::string>> v = convertPolynomial(polyString);
    char **resStr = new char *[v.size() * 2];
    polySize = v.size();
    for (size_t i = 0; i < v.size(); ++i)
    {
        resStr[i * 2] = new char[v[i].first.size() + 1];
        resStr[i * 2 + 1] = new char[v[i].second.size() + 1];

        resStr[i * 2][v[i].first.size()] = '\0';
        resStr[i * 2 + 1][v[i].second.size()] = '\0';

        strcpy(resStr[i * 2], v[i].first.c_str());
        strcpy(resStr[i * 2 + 1], v[i].second.c_str());
    }
    return resStr;
}
/**
 * Performs polynomial addition and returns the result as a string.
 *
 * @param retSize       The size of the resulting polynomial.
 * @param polySize1     The size of the first polynomial.
 * @param polyStr1      The string array representation of the first polynomial.
 * @param polySize2     The size of the second polynomial.
 * @param polyStr2      The string array representation of the second polynomial.
 * @param numModStr     The modulus value as a string.
 * @param errorStr      The error message string.
 * @return              The result of polynomial addition as a string.
 */
extern "C" char *
polyAddition(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
             char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1 + poly2;

        std::string resString = polyRes.toString();

        char *resStr = new char[resString.size() + 1];
        strcpy(resStr, resString.c_str());

        retSize = resString.size() + 1;
        return resStr;
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}
/**
 * Performs polynomial subtraction and returns the result as a string.
 *
 * @param retSize       The size of the resulting polynomial.
 * @param polySize1     The size of the first polynomial.
 * @param polyStr1      The string array representation of the first polynomial.
 * @param polySize2     The size of the second polynomial.
 * @param polyStr2      The string array representation of the second polynomial.
 * @param numModStr     The modulus value as a string.
 * @param errorStr      The error message string.
 * @return              The result of polynomial subtraction as a string.
 */

extern "C" char *
polySubstruction(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2,
                 char **polyStr2, char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1 - poly2;

        std::string resString = polyRes.toString();

        char *resStr = new char[resString.size() + 1];
        strcpy(resStr, resString.c_str());

        retSize = resString.size() + 1;
        return resStr;
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}
/**
 * Performs polynomial multiplication and returns the result as a string.
 *
 * @param retSize       The size of the resulting polynomial.
 * @param polySize1     The size of the first polynomial.
 * @param polyStr1      The string array representation of the first polynomial.
 * @param polySize2     The size of the second polynomial.
 * @param polyStr2      The string array representation of the second polynomial.
 * @param numModStr     The modulus value as a string.
 * @param errorStr      The error message string.
 * @return              The result of polynomial multiplication as a string.
 */
extern "C" char *
polyMultiplication(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2,
                   char **polyStr2, char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1 * poly2;

        std::string resString = polyRes.toString();

        char *resStr = new char[resString.size() + 1];
        strcpy(resStr, resString.c_str());

        retSize = resString.size() + 1;
        return resStr;
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}

/**
 * Performs polynomial division and returns the result as a string.
 *
 * @param retSize       The size of the resulting polynomial.
 * @param polySize1     The size of the first polynomial.
 * @param polyStr1      The string array representation of the first polynomial.
 * @param polySize2     The size of the second polynomial.
 * @param polyStr2      The string array representation of the second polynomial.
 * @param numModStr     The modulus value as a string.
 * @param errorStr      The error message string.
 * @return              The result of polynomial division as a string.
 */
extern "C" char *
polyDivision(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
             char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1 / poly2;

        std::string resString = polyRes.toString();

        char *resStr = new char[resString.size() + 1];
        strcpy(resStr, resString.c_str());

        retSize = resString.size() + 1;
        return resStr;
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}

/**
 * Performs polynomial division and returns the remainder as a string.
 *
 * @param retSize       The size of the resulting polynomial.
 * @param polySize1     The size of the first polynomial.
 * @param polyStr1      The string array representation of the first polynomial.
 * @param polySize2     The size of the second polynomial.
 * @param polyStr2      The string array representation of the second polynomial.
 * @param numModStr     The modulus value as a string.
 * @param errorStr      The error message string.
 * @return              The remainder of polynomial division as a string.
 */
extern "C" char *
polyRest(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
         char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1 % poly2;

        std::string resString = polyRes.toString();

        char *resStr = new char[resString.size() + 1];
        strcpy(resStr, resString.c_str());

        retSize = resString.size() + 1;
        return resStr;
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}

/**
 * Calculates the greatest common divisor (GCD) of two polynomials and returns the result as a string.
 *
 * @param retSize       The size of the resulting polynomial.
 * @param polySize1     The size of the first polynomial.
 * @param polyStr1      The string array representation of the first polynomial.
 * @param polySize2     The size of the second polynomial.
 * @param polyStr2      The string array representation of the second polynomial.
 * @param numModStr     The modulus value as a string.
 * @param errorStr      The error message string.
 * @return              The GCD of the two polynomials as a string.
 */
extern "C" char *
polyGCD(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
        char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1.gcd(poly2);

        std::string resString = polyRes.toString();

        char *resStr = new char[resString.size() + 1];
        strcpy(resStr, resString.c_str());

        retSize = resString.size() + 1;
        return resStr;
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}
/**
 * Calculates the derivative of a polynomial and returns the result as a string.
 *
 * @param retSize       The size of the resulting polynomial.
 * @param polySize1     The size of the polynomial.
 * @param polyStr1      The string array representation of the polynomial.
 * @param numModStr     The modulus value as a string.
 * @param errorStr      The error message string.
 * @return              The derivative of the polynomial as a string.
 */

extern "C" char *
polyDerivative(size_t &retSize, size_t polySize1, char **polyStr1, char *numModStr,
               char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        poly1.print();

        Polynomial<mpz_class> polyRes = poly1.der();
        polyRes.print();

        std::string resString = polyRes.toString();
        retSize = resString.size() + 1;
        char *resStr = new char[resString.size() + 1];
        strcpy(resStr, resString.c_str());

        return resStr;
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}

/**
 * Evaluates a polynomial at a given point and returns the result as a string.
 *
 * @param retSize       The size of the resulting polynomial.
 * @param polySize1     The size of the polynomial.
 * @param polyStr1      The string array representation of the polynomial.
 * @param numModStr     The modulus value as a string.
 * @param evalPointStr  The evaluation point as a string.
 * @param errorStr      The error message string.
 * @return              The result of polynomial evaluation as a string.
 */
extern "C" char *
polyEvaluate(size_t &retSize, size_t polySize1, char **polyStr1, char *numModStr,
             char *evalPointStr, char *errorStr)
{
    try
    {
        mpz_class numMod, evalPoint;

        evalPoint.set_str(evalPointStr, 10);

        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);

        mpz_class ret = poly1.evaluate(evalPoint).getValue();
        retSize = ret.get_str().size() + 1;
        char *retStr = new char[MESSAGE_LEN];
        strcpy(retStr, ret.get_str().c_str());

        return retStr;
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}
/**
 * Returns the string representation of a cyclotomic polynomial of a given order.
 *
 * @param retSize       The size of the resulting polynomial.
 * @param orderStr      The order of the cyclotomic polynomial as a string.
 * @param numModStr     The modulus value as a string.
 * @param errorStr      The error message string.
 * @return              The string representation of the cyclotomic polynomial.
 */
extern "C" char *
getCyclotomic(size_t &retSize, char *orderStr, char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);
        size_t order = atol(orderStr);

        Polynomial<mpz_class> polyOrdered;
        polyOrdered.fromCyclotomic(order, numMod);

        std::string resString = polyOrdered.toString();
        retSize = resString.size() + 1;
        char *resStr = new char[resString.size() + 1];
        strcpy(resStr, resString.c_str());

        return resStr;
    }
    catch (const std::exception &e)
    {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}
