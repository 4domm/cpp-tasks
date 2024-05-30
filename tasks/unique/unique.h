#pragma once

template <typename T>
T Unique(T begin, T end) {
    T right_pointer = begin;
    while (right_pointer < end) {
        while (right_pointer + 1 < end && *right_pointer == *(right_pointer + 1)) {
            ++right_pointer;
        }
        *begin = *right_pointer;
        ++right_pointer;
        ++begin;
    }
    return begin;
}