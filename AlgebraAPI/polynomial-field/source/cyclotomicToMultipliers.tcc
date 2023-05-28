// #ifndef CYCLOTOMIC_TO_MULTIPLIERS
// #define CYCLOTOMIC_TO_MULTIPLIERS

// #include "../poly-field-math.h"
// #include "../../finite-field/mod-math.h"
// #include <cmath>
// #include <queue>

// using namespace modular;

// template <typename T>
// T numberGCD(T a, T b) {
//     if (a == 0) return b;
//     return numberGCD(b % a, a);
// }

// template <typename T>
// T calcM(T num, T MOD, T i) {
//     T m = 1;
//     while ((T)pow(MOD, m) % (num / numberGCD(i, num)) != 1) m++;

//     return m;
// }

// template <typename T>
// T calcD(T num, T MOD) {
//     T d = 1;
//     while ((T)pow(num, d) % MOD != 1) d++;

//     return d;
// }

// template <typename T>
// T generateRi(T num, T MOD, T i) {
//     T m = calcM(num, MOD, i);
//     Polynomial<T> res = Polynomial(MOD);
//     for (T j = 0; j < m; j++)
//         res.addNode(Node(1, i * (T)pow(q, j)));

//     return res;
// }

// template <typename T>
// std::vector<PolynomialField<T>> PolynomialField<T>::cyclotomicToMultipliers(T num, T mod) {
//     std::vector<PolynomialField<T>> res;
//     Polynomial<T> cyclotomic; cyclotomic.fromCyclotomic(num, mod);
//     T expDegree = calcD(num, MOD);
//     bool added = 0;

//     std::queue<Polynomial<T>> q;
//     Polynomial<T> tmpOutter, tmpInner;
//     q.push(cyclotomic);
//     while(!q.empty())
//     {
//         if (i % num == 0) i++;
//         tmpOutter = q.front();

//         if (tmpOutter.getDegree() == expDegree) {
//             res.push_back(PolynomialField(MOD, tmpOutter));
//             q.pop();
//         }
//         else if (tmpOutter.getDegree() == 0)
//             q.pop();
//         else {
//             T size = tmpOutter.getDegree();
//             Polynomial<T> Ri = generateRi(num, MOD, i);
//             Polynomial<T> newR;
//             for (T j = 0; j < MOD; j++)
//             {
//                 tmpInner = tmpOutter;
//                 newR = Ri.addNode(j, 0);
//                 tmpInner = tmpOutter.gcd(newR);

//                 if (tmpInner.getDegree() > 0 && tmpInner.getDegree() < size) {
//                     q.push(tmpInner);
//                     added = 1;
//                 }
//             }
//             if (added) {
//                 q.pop();
//                 added = 0;
//             }
//             i++;
//         }
//     }

//     return res;
// }

// #endif