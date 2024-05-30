#pragma once
#include "tuple"
template <typename Iterable>
class EnumIterator {
public:
    explicit EnumIterator(Iterable& iter) : iter_(iter), index_(0), begin_(std::begin(iter)), end_(std::end(iter)) {
    }
    EnumIterator& operator++() {
        ++begin_;
        ++index_;
        return *this;
    }
    bool operator!=(const EnumIterator& rhs) const {
        return begin_ != end_;
    }
    auto begin() const {  // NOLINT
        return *this;
    }

    auto end() const {  // NOLINT
        return *this;
    }
    auto operator*() const {
        return std::tie(index_, *begin_);
    }

private:
    Iterable iter_;
    std::size_t index_;
    decltype(std::begin(iter_)) begin_;
    decltype(std::end(iter_)) end_;
};
template <typename Iterable>
auto Enumerate(Iterable&& iter) {
    return EnumIterator<Iterable>(iter);
}