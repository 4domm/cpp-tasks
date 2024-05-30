#include "factorization.h"

#include <cstdint>
std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    int64_t current_number = x;
    std::vector<std::pair<int64_t, int>> result;
    for (int64_t current_divider = 2; current_divider * current_divider <= current_number; ++current_divider) {
        while (current_number % current_divider == 0) {
            if (!result.empty()) {
                if (result[result.size() - 1].first == current_divider) {
                    result[result.size() - 1].second = ++result[result.size() - 1].second;
                } else {
                    result.emplace_back(current_divider, 1);
                }
            } else {
                result.emplace_back(current_divider, 1);
            }
            current_number /= current_divider;
        }
    }
    if (current_number != 1) {
        result.emplace_back(current_number, 1);
    }
    return result;
}
