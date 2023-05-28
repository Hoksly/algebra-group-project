#include <random>

#include "../mod-math.h"
namespace modular {
#ifndef TASK_10
#define TASK_10

/**
 *  @brief Probabilistic check of a number for simplicity (Miller-Rabin test)
 *  @param  base value
 *  @param  k  the number of iteration of of the algorithm
 *
 *
 *  @return returns TRUE if value is probably prime, FALSE if value is compound
 */

template <typename T1>
bool
isPrime(modNum<T1> base, size_t k) {
    T1 value = base.getValue();

    // Edge case
    if (value == 3 || value == 2)
        return true;
    if (value <= 1 || value == 4 || value % 2 == 0)
        return false;

    // Set k to a default value of 1 if it is less than 1
    if (k < 1)
        k = 1;

    T1 up = value - 1;
    T1 s = 0;

    while (up % 2 == 0) {
        up /= 2;
        s++;
    }

    // Repeat the test k times
    for (size_t i = 0; i < k; i++) {
        // Choose a random integer a between 2 and value-2
        T1 rand_number = rand() % (value - 4) + 2;

        // Compute y = rand_number^up mod value
        T1 y = fpow(modNum<T1>(rand_number, value), up).getValue();

        if (y != 1 && y != value - 1) {
            for (T1 j = 0; j < s && y != value - 1; j++) {
                y = (fpow(modNum<T1>(y, value), static_cast<T1>(2)).getValue());

                // If y == 1, value is composite
                if (y == 1)
                    return false;
            }

            // If y != value-1, value is composite
            if (y != value - 1)
                return false;
        }
    }

    // If the test has not found a composite value, value is probably prime
    return true;
}
#endif
}   // namespace modular