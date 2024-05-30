#pragma once

template <class T>
class UniquePtr {
public:
    explicit UniquePtr(T* ptr = nullptr) : ptr_(ptr) {
    }
    ~UniquePtr() {
        delete ptr_;
    }
    UniquePtr(UniquePtr&& other) : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }
    T* operator->() const {
        return ptr_;
    }
    void Reset(T* ptr = nullptr) {
        if (ptr != ptr_) {
            delete ptr_;
            ptr_ = ptr;
        }
    }

private:
    T* ptr_;
};
