#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>

template <class T>
class Array {
private:
    size_t size_;
    T* data_;

public:
    Array() : size_(0), data_(nullptr) {
    }

    explicit Array(size_t size) {
        size_ = size;
        if (size == 0) {
            data_ = nullptr;
        } else {
            data_ = new T[size];
        }
    }

    Array(std::initializer_list<T> list) {
        size_ = list.size();
        data_ = new T[size_];
        std::copy(list.begin(), list.end(), data_);
    }

    Array(const Array& other) : Array() {
        *this = other;
    }

    Array& operator=(const Array& other) {
        delete[] data_;
        size_ = other.size_;
        data_ = new T[size_];
        std::copy(other.data_, other.data_ + size_, data_);
        return *this;
    }
    ~Array() {
        delete[] data_;
        size_ = 0;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    size_t size() const {  // NOLINT
        return size_;
    }

    class Iterator {
    public:
        explicit Iterator(T* current) : current_(current) {
        }
        Iterator& operator++() {
            ++current_;
            return *this;
        }

        T& operator*() {
            return *current_;
        }

        bool operator!=(const Iterator& other) {
            return current_ != other.current_;
        }

    private:
        T* current_;
    };

    Iterator begin() const {  // NOLINT
        return Iterator(data_);
    }

    Iterator end() const {  // NOLINT
        return Iterator(data_ + size_);
    }
};
