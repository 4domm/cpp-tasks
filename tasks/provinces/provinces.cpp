#include "provinces.h"

#include <cstdint>
#include <queue>
int64_t CountPassports(const std::vector<int>& provinces) {
    if (provinces.size() == 1) {
        return provinces[0];
    }
    if (provinces.size() == 2) {
        return provinces[0] + provinces[1];
    }
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<>> minimal_queue(provinces.begin(),
                                                                                     provinces.end());
    int64_t answer = 0;
    while (minimal_queue.size() != 1) {
        int64_t first_minimal = minimal_queue.top();
        minimal_queue.pop();
        int64_t second_minimal = minimal_queue.top();
        minimal_queue.pop();
        minimal_queue.push(first_minimal + second_minimal);
        answer += second_minimal + first_minimal;
    }
    return answer;
}
