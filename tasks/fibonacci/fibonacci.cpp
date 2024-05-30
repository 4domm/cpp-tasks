#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t first_cache = 0;
    int64_t second_cache = 1;
    int64_t answer = 1;
    if (n == 0) {
        return first_cache;
    }
    for (int i = 2; i <= n; i++) {
        answer = first_cache + second_cache;
        first_cache = second_cache;
        second_cache = answer;
    }
    return answer;
}
