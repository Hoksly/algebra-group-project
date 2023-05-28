
#include <gmpxx.h>
#include "../custom-hash.h"
#include <random>

#include "../../mod-math.h"
#include "utils.h"

int main()
{

    mpz_class a = 3;
    mpz_class b = 5;
    mpz_class mod = 103;

    mpz_class lg = modular::log(modular::modNum<mpz_class>(a, mod), modular::modNum<mpz_class>(b, mod));

    std::cout << lg.get_str() << std::endl;
    return 0;
}
