#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    for (int i = 0; i < end - begin; ++i) {
        for (int j = 0; j < end - begin - 1; ++j) {
            if (!comparator(*(begin + j), *(begin + j + 1))) {
                std::swap(*(begin + j), *(begin + j + 1));
            }
        }
    }
}
