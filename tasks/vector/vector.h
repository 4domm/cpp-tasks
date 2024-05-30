#pragma once
#include <algorithm>
#include <cstddef>
template <class T>
class Vector {
private:
    int* data_;
    size_t size_;
    size_t capacity_;

public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {
    }
    explicit Vector(size_t size) : data_(nullptr), size_(size), capacity_(size) {
        if (size != 0) {
            data_ = new int[size];
            std::fill(data_, data_ + size, 0);
        }
    }
    Vector(std::initializer_list<int> init_list) : Vector(init_list.size()) {
        std::copy(init_list.begin(), init_list.end(), data_);
    }
    Vector(const Vector& other) : Vector(other.size_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
    Vector(Vector&& other) : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    Vector& operator=(const Vector& other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new int[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
        return *this;
    }
    Vector& operator=(Vector&& other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new int[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
        return *this;
    }
    ~Vector() {
        delete[] data_;
    }
    void Swap(Vector& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
    int operator[](size_t index) const {
        return data_[index];
    }
    int& operator[](size_t index) {
        return data_[index];
    }
    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return capacity_;
    }
    void PushBack(int value) {
        if (size_ >= capacity_) {
            size_t new_capacity = (capacity_ == 0 ? 1 : capacity_ * 2);
            int* new_data = new int[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
        data_[size_] = value;
        ++size_;
    }
    void PopBack() {
        if (size_) {
            --size_;
        }
    }
    void Clear() {
        size_ = 0;
    }
    void Reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            int* new_data = new int[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }
    int* Begin() {
        return data_;
    }

    int* End() {
        return data_ + size_;
    }
    class Iterator : public std::iterator<std::random_access_iterator_tag, int> {
    public:
        Iterator() : ptr_(nullptr) {
        }
        explicit Iterator(int* ptr) : ptr_(ptr) {
        }
        Iterator(const Iterator& other) : ptr_(other.ptr_) {
        }
        Iterator& operator++() {
            ++ptr_;
            return *this;
        }
        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                ptr_ = other.ptr_;
            }
            return *this;
        }
        Iterator& operator=(int* ptr) {
            ptr_ = ptr;
            return *this;
        }

        int* operator->() const {
            return ptr_;
        }

        T& operator*() {
            return *ptr_;
        }
        Iterator operator++(int) {
            Iterator temp(*this);
            ++ptr_;
            return temp;
        }
        Iterator& operator--() {
            --ptr_;
            return *this;
        }
        Iterator operator--(int) {
            Iterator temp(*this);
            --ptr_;
            return temp;
        }
        Iterator operator+(int n) const {
            return Iterator(ptr_ + n);
        }
        Iterator operator-(int n) const {
            return Iterator(ptr_ - n);
        }
        int operator-(const Iterator& other) const {
            return ptr_ - other.ptr_;
        }
        bool operator!=(const Iterator& other) {
            return ptr_ != other.ptr_;
        }

    private:
        int* ptr_;
    };

    Iterator begin() const {  // NOLINT
        return Iterator(data_);
    }

    Iterator end() const {  // NOLINT
        return Iterator(data_ + size_);
    }
};
