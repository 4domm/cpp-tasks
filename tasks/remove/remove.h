#pragma once

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    T left_pointer = begin;
    T right_pointer = begin;
    while (right_pointer != end) {
        if (*right_pointer != value) {
            *left_pointer = *right_pointer;
            ++left_pointer;
        }
        ++right_pointer;
    }
    return left_pointer;
}