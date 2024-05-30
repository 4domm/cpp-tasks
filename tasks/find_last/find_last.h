#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    Iterator result = last;
    while (first != last) {
        if (*first == val) {
            result = first;
        }
        first++;
    }
    return result;
}
