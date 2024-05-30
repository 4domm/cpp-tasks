#pragma once

#include <iterator>

template <typename Container>
class Reversed {
public:
    explicit Reversed(Container& container)
        : container_(container), begin_(std::rbegin(container_)), end_(std::rend(container_)) {
    }

    auto begin() const {  // NOLINT
        return begin_;
    }
    auto end() const {  // NOLINT
        return end_;
    }

private:
    Container& container_;
    decltype(std::rbegin(container_)) begin_;
    decltype(std::rend(container_)) end_;
};
