#include <cmath>
#include <map>
#include <vector>

#include "../mod-math.h"

using namespace std;
namespace modular {

#ifndef EULER_CARMICAEL
#define EULER_CARMICAEL

template <typename T>
T
EulerFunction(T n) {
    if (n <= static_cast<T>(0))
        throw logic_error("Euler totient function is not defiend on non Natural values");

    T res = n;

    for (T p = static_cast<T>(2); p * p <= n; p += static_cast<T>(1)) {
        if (n % p == static_cast<T>(0)) {
            while (n % p == static_cast<T>(0)) n /= p;
            res -= res / p;
        }
    }

    if (n > static_cast<T>(1))
        res -= res / n;
    return res;
}

template <typename T>
modNum<T>
eulerFunction(modNum<T> num) {
    return modNum<T>(static_cast<T>(EulerFunction<T>(num.getValue())), num.getMod());
}

template <typename T>
T
mygcd(T a, T b) {
    while (b) {
        T t = a % b;
        a = b;
        b = t;
    }
    return a;
}

template <typename T>
T
CarmichaelFunction(T n) {
    if (n <= static_cast<T>(0))
        throw logic_error("Euler totient function is not defiend on non Natural values");

    if (n == static_cast<T>(1))
        return static_cast<T>(1);
    std::vector<T> factors;
    for (T i = static_cast<T>(2); i * i <= n; i += static_cast<T>(2)) {
        T w = static_cast<T>(0);
        while (n % i == static_cast<T>(0)) {
            w++;
            n /= i;
        }
        if (i == static_cast<T>(2) && w >= static_cast<T>(3)){
            T power = fpow<T>(modNum<T>(i, i+1), w-1).getValue();
            factors.push_back((power * (i - 1)) / 2);
        }
        else if (i >= 2 && w > 0){
            T power = fpow<T>(modNum<T>(i, i+1), w-1).getValue();
            factors.push_back(power * (i - 1));
        }
        if (i == 2)
            i--;
    }
    if (n != 1)
        factors.push_back(n - 1);

    T res = 1;
    for (auto i : factors) res *= i / mygcd(res, i);
    return res;
}

long long Carmichael(long long n){
	if (n < 1) return 0;
	if (n == 1) return 1;
	std::vector<long long> factors;
	for(long long i = 2; i*i <= n; i += 2){
		long long w = 0;
		while(n % i == 0){
			w++;
			n /= i;
		}
		if (i == 2 && w >= 3){
            long long power = std::pow(i, w-1);
			factors.push_back((power * (i-1))/2);
        }
		else if(i >= 2 && w > 0)
			factors.push_back(std::pow(i, w-1) * (i-1));
		if(i == 2) i--;
	}
	if(n != 1) factors.push_back(n-1);
    long long res = 1;
for(auto i : factors)
	res *= i/mygcd<long long>(res, i);
return res;
}

#endif

}   // namespace modular
