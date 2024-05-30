#include "sum_digits.h"
int64_t SumOfDigits(int64_t number) {
    const int k = 10;
    int64_t ans = 0;
    while (number != 0) {
        ans += number % k;
        number /= k;
    }
    return ans;
}
