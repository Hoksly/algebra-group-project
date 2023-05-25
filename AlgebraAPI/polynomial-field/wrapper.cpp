#include <gmpxx.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "poly-field-math.h"

const size_t MESSAGE_LEN = 200;

vector<std::pair<mpz_class, size_t>>
stringToPolyVector1(char **polyString, size_t polySize, mpz_class numMod)
{
    vector<std::pair<mpz_class, size_t>> polyV(polySize);

    for (size_t i = 0; i < polySize; ++i)
    {
        mpz_class a;
        std::cout << std::string(polyString[i * 2]) << std::endl;
        a.set_str(polyString[i * 2], 10);

        std::string s(polyString[i * 2 + 1]);
        std::stringstream sstream(s);
        size_t b;
        sstream >> b;

        polyV[i] = make_pair(a, b);
    }

    return polyV;
}

char **
stringToPolyVector1(vector<std::pair<mpz_class, size_t>> polyV)
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

std::string
removeSpaces1(std::string str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

std::vector<std::pair<std::string, std::string>>
convertPolynomial1(std::string polynomial)
{
    polynomial = removeSpaces1(polynomial);
    std::vector<std::pair<std::string, std::string>> result;
    std::stringstream ss(polynomial);
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

extern "C" char **
polyParse1(size_t &polySize, char *polyString)
{
    std::vector<std::pair<std::string, std::string>> v = convertPolynomial1(polyString);
    char **resStr = new char *[v.size() * 2];
    polySize = v.size();
    for (size_t i = 0; i < v.size(); ++i)
    {
        resStr[i * 2] = new char[v[i].first.size() + 1];
        resStr[i * 2 + 1] = new char[v[i].second.size() + 1];

        strcpy(resStr[i * 2], v[i].first.c_str());
        strcpy(resStr[i * 2 + 1], v[i].second.c_str());
    }
    return resStr;
}

extern "C" char *
polyFieldAddition(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
                  size_t polyModSize, char **polyModStr,
                  char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> polyRaw1(stringToPolyVector1(polyStr1, polySize1, numMod), numMod);
        std::string s(polyStr2[1]);

        Polynomial<mpz_class> polyRaw2(stringToPolyVector1(polyStr2, polySize2, numMod), numMod);
        Polynomial<mpz_class> polyMod(stringToPolyVector1(polyModStr, polyModSize, numMod), numMod);

        PolynomialField<mpz_class> poly1(numMod, polyMod, polyRaw1);
        PolynomialField<mpz_class> poly2(numMod, polyMod, polyRaw1);

        PolynomialField<mpz_class> polyRes = poly1 + poly2;

        std::string resString = polyRes.getValue().toString();

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

extern "C" char *
polyFieldSubstruction(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
                      size_t polyModSize, char **polyModStr,
                      char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> polyRaw1(stringToPolyVector1(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> polyRaw2(stringToPolyVector1(polyStr2, polySize2, numMod), numMod);
        Polynomial<mpz_class> polyMod(stringToPolyVector1(polyModStr, polyModSize, numMod), numMod);

        PolynomialField<mpz_class> poly1(numMod, polyMod, polyRaw1);
        PolynomialField<mpz_class> poly2(numMod, polyMod, polyRaw1);

        PolynomialField<mpz_class> polyRes = poly1 - poly2;

        std::string resString = polyRes.getValue().toString();

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

extern "C" char *
polyFieldMultiplication(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
                        size_t polyModSize, char **polyModStr,
                        char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> polyRaw1(stringToPolyVector1(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> polyRaw2(stringToPolyVector1(polyStr2, polySize2, numMod), numMod);
        Polynomial<mpz_class> polyMod(stringToPolyVector1(polyModStr, polyModSize, numMod), numMod);

        PolynomialField<mpz_class> poly1(numMod, polyMod, polyRaw1);
        PolynomialField<mpz_class> poly2(numMod, polyMod, polyRaw1);

        PolynomialField<mpz_class> polyRes = poly1 * poly2;

        std::string resString = polyRes.getValue().toString();

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

extern "C" char *
polyFieldDivision(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
                  size_t polyModSize, char **polyModStr,
                  char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> polyRaw1(stringToPolyVector1(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> polyRaw2(stringToPolyVector1(polyStr2, polySize2, numMod), numMod);
        Polynomial<mpz_class> polyMod(stringToPolyVector1(polyModStr, polyModSize, numMod), numMod);

        PolynomialField<mpz_class> poly1(numMod, polyMod, polyRaw1);
        PolynomialField<mpz_class> poly2(numMod, polyMod, polyRaw1);

        PolynomialField<mpz_class> polyRes = poly1 / poly2;

        std::string resString = polyRes.getValue().toString();

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

extern "C" char *
polyFieldInversion(size_t &retSize, size_t polySize1, char **polyStr1,
                   size_t polyModSize, char **polyModStr,
                   char *numModStr, char *errorStr)
{
    try
    {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> polyRaw1(stringToPolyVector1(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> polyMod(stringToPolyVector1(polyModStr, polyModSize, numMod), numMod);

        PolynomialField<mpz_class> poly1(numMod, polyMod, polyRaw1);

        PolynomialField<mpz_class> polyRes = poly1.inv();

        std::string resString = polyRes.getValue().toString();

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
