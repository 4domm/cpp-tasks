#pragma once

#include <set>
#include <string>
struct Count {
    size_t shared;
    size_t weak;
    bool weak_exp = false;
    Count(size_t s, size_t w) {
        shared = s;
        weak = w;
    }
};
template <class T>
class WeakPtr;
template <class T>
class SharedPtr {
    friend class WeakPtr<T>;
    T* obj_ = nullptr;
    Count* count_ = nullptr;

public:
    SharedPtr() {
        obj_ = nullptr;
        count_ = new Count(1, 0);
    }
    ~SharedPtr() {
        --count_->shared;
        if (count_->shared == 0) {
            delete obj_;
            obj_ = nullptr;
            count_->weak_exp = true;
            if (!count_->weak) {
                delete count_;
            }
        }
    }

    SharedPtr(const SharedPtr<T>& other) {
        if (other.obj_) {
            obj_ = other.obj_;
            count_ = other.count_;
            ++count_->shared;
        } else {
            count_ = new Count(1, 0);
        }
    }

    SharedPtr(SharedPtr<T>&& other) {
        obj_ = other.obj_;
        count_ = other.count_;
        other.count_ = new Count(1, 0);
        other.obj_ = nullptr;
    }

    void RemoveValue() {
        --count_->shared;
        if (count_->shared == 0) {
            delete obj_;
            obj_ = nullptr;
        }
        if (count_->shared + count_->weak == 0) {
            delete count_;
        }
    }
    void operator=(const SharedPtr<T>& other) {
        RemoveValue();
        if (other.obj_ != nullptr) {
            obj_ = other.obj_;
            count_ = other.count_;
            ++count_->shared;
        } else {
            count_ = new Count(1, 0);
            obj_ = nullptr;
        }
    }
    void operator=(SharedPtr<T>&& other) {
        RemoveValue();
        if (other.obj_) {
            obj_ = other.obj_;
            count_ = other.count_;
            other.count_ = new Count(1, 0);
            other.obj_ = nullptr;
        } else {
            count_ = new Count(1, 0);
        }
    }
    explicit SharedPtr(T* value) {
        obj_ = value;
        count_ = new Count(1, 0);
    }

    T operator*() {
        return *obj_;
    }

    void Reset(T* object) {
        RemoveValue();
        obj_ = object;
        count_ = new Count(1, 0);
    }

    T* Get() {
        return obj_;
    }

    explicit SharedPtr(const WeakPtr<T>& rhs);
};

template <class T>
class WeakPtr {
    friend class SharedPtr<T>;
    T* obj_ = nullptr;
    Count* count_ = nullptr;

public:
    WeakPtr() {
        obj_ = nullptr;
        count_ = new Count(0, 1);
        count_->weak_exp = true;
    }

    ~WeakPtr() {
        --count_->weak;

        if (!count_->shared) {
            if (!count_->weak_exp) {
                delete obj_;
                obj_ = nullptr;
                count_->weak_exp = true;
            }
            if (count_->weak == 0) {
                delete count_;
            }
        }
    }

    WeakPtr(const WeakPtr<T>& other) {
        obj_ = other.obj_;
        count_ = other.count_;
        ++count_->weak;
    }

    explicit WeakPtr(const SharedPtr<T>& other) {
        if (other.obj_) {
            obj_ = other.obj_;
            count_ = other.count_;
            ++count_->weak;
        } else {
            obj_ = nullptr;
            count_ = new Count(0, 1);
            count_->weak_exp = true;
        }
    }

    WeakPtr(WeakPtr<T>&& other) {
        obj_ = other.obj_;
        count_ = other.count_;
        other.count_ = new Count(0, 1);
        other.obj_ = nullptr;
        ++count_->weak;
    }

    bool IsExpired() {
        return count_->weak_exp || obj_ == nullptr;
    }
    void RemoveValue() {
        --count_->weak;
        if (count_->shared == 0 && count_->weak == 0) {
            delete obj_;
            obj_ = nullptr;
            delete count_;
            count_ = nullptr;
        }
    }
    void operator=(const WeakPtr<T>& other) {
        RemoveValue();
        if (other.obj_) {
            obj_ = other.obj_;
            count_ = other.count_;
            ++count_->weak;
        } else {
            obj_ = nullptr;
            count_ = new Count(0, 1);
            count_->weak_exp = true;
        }
    }

    void operator=(WeakPtr<T>&& other) {
        RemoveValue();
        obj_ = other.obj_;
        count_ = other.count_;
        other.count_ = new Count(0, 1);
        other.obj_ = nullptr;
    }

    explicit WeakPtr(T* value) {
        obj_ = value;
        count_ = new Count(0, 1);
    }

    T operator*() {
        return *obj_;
    }

    void Reset(T* object) {
        RemoveValue();
        obj_ = object;
        count_ = new Count(0, 1);
    }

    T* Get() {
        if (count_->weak_exp) {
            return nullptr;
        }
        return obj_;
    }

    SharedPtr<T> Lock() {
        return SharedPtr<T>(*this);
    }
};

template <class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& rhs) {
    if (!rhs.count_->weak_exp && rhs.obj_) {
        obj_ = rhs.obj_;
        count_ = rhs.count_;
        ++count_->shared;
    } else {
        obj_ = nullptr;
        count_ = new Count(1, 0);
    }
}
