#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> range;
    if (from - to == 0 || step == 0 || (from > to && step > 0) || (to > from && step < 0)) {
        return range;
    }
    if (step > 0) {
        for (int i = from; i < to; i += step) {
            range.push_back(i);
        }
    } else {
        for (int j = from; j > to; j += step) {
            range.push_back(j);
        }
    }
    return range;
}
