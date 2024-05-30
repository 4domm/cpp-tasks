#include "reduce_fraction.h"

#include <numeric>

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t nod = std::gcd(numerator, denominator);
    return numerator / nod + denominator / nod;
}
