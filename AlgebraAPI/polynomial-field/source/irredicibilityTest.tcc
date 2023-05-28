#include "../poly-field-math.h"
#include "../../polynomial-ring/poly-ring-math.h"
#include "../../finite-field/mod-math.h"

#define TRINOMIAL_DEGREE  859433
#define TRINOMIAL_SECOND_DEGREE  170340

template <typename T>
bool
irreducibilityTest(Polynomial<T> p){
    Polynomial<T> t (static_cast<T>(898181));
    t.addNode(Node<T>(modNum<T>(1, 898181), TRINOMIAL_DEGREE));
    t.addNode(Node<T>(modNum<T>(1, 898181), TRINOMIAL_SECOND_DEGREE));
    t.addNode(Node<T>(modNum<T>(1, 898181), 0));

    PolynomialField<T> P(p.getNumMod(), t);
    for (auto i = p.begin(); i!=p.end(); i++){
        Node<T> tmp = *i;
        P.addNode(tmp);
    }

    for (T i=1; i<=static_cast<T>(TRINOMIAL_DEGREE); i++){
        PolynomialField<T> tmp = P.pow(2);
        P = tmp;
    }

    Polynomial<T> res = P.getValue();
    Node<T> first = res[0];

    if (res.size() == 1 && first.deg() == 1 && first.k().getValue() == 1)
        return true;
    else
        return false;
}