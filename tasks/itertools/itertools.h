#pragma once
#include "utility"
#include "vector"
template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};
template <class T>
class RangeIterator {
public:
    explicit RangeIterator(T value = 0, T step = 1) : current_(value), step_(step) {
    }
    T operator*() const {
        return current_;
    }
    RangeIterator& operator++() {
        current_ += step_;
        return *this;
    }
    bool operator==(const RangeIterator& rhs) const {
        return current_ == rhs.current_ && step_ == rhs.step_;
    }

    bool operator!=(const RangeIterator& rhs) const {
        return !operator==(rhs);
    }

private:
    T current_;
    const T step_;
};

template <class T>
auto Range(T begin, T end, T step = 1) {
    auto start = RangeIterator(begin, step);
    if ((begin < end) ^ (0 < step)) {
        return IteratorRange(start, start);
    }
    if (end % step != begin % step) {
        end += (step - (end - begin) % step);
    }
    return IteratorRange(start, RangeIterator(end, step));
}

template <class T>
IteratorRange<RangeIterator<T>> Range(T end) {
    return Range(static_cast<T>(0), end, static_cast<T>(1));
}

template <class FirstIterator, class SecondIterator>
class ZipIterator {
public:
    ZipIterator(FirstIterator first, SecondIterator second) : first_(first), second_(second) {
    }

    auto operator*() const {
        return std::make_pair(*first_, *second_);
    }

    ZipIterator& operator++() {
        ++first_;
        ++second_;
        return *this;
    }
    bool operator!=(const ZipIterator& rhs) const {
        return !(first_ == rhs.first_ || second_ == rhs.second_);
    }

private:
    FirstIterator first_;
    SecondIterator second_;
};

template <class FirstContainer, class SecondContainer>
auto Zip(const FirstContainer& first, const SecondContainer& second) {
    auto begin = ZipIterator(first.begin(), second.begin());
    auto end = ZipIterator(first.end(), second.end());
    return IteratorRange(begin, end);
}

template <class Container>
auto Group(const Container& container) {
    std::vector<IteratorRange<typename Container::const_iterator>> result;
    auto begin = container.begin();
    auto end = container.begin();
    while (begin != container.end()) {
        while (end != container.end() && (*begin == *end)) {
            ++end;
        }
        result.push_back(IteratorRange(begin, end));
        begin = end;
    }

    return result;
}