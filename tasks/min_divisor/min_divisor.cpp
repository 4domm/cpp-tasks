#include "min_divisor.h"

int64_t MinDivisor(int64_t number) {
    const int a = 5;
    const int b = 7;
    if (number % 2 == 0) {
        return 2;
    }
    if (number % 3 == 0) {
        return 3;
    }
    if (number % a == 0) {
        return a;
    }
    if (number % b == 0) {
        return b;
    }
    return number;
}
