#pragma once

template <typename T>
T IsSortedUntil(T begin, T end) {
    T previous = begin;
    for (T i = begin; i <= end; ++i) {
        if (*begin < *previous) {
            return begin;
        }
        previous = begin;
        ++begin;
    }
    return end;
}
