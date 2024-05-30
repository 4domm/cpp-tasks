#include "hypotenuse.h"
double CalculateHypotenuse(int64_t a, int64_t b) {
    return sqrt(pow(static_cast<double>(a), 2) + pow(static_cast<double>(b), 2));
};
