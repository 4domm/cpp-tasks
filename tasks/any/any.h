#pragma once

#include <typeinfo>

#include "algorithm"
class Any {
private:
    struct Base {
        virtual ~Base() = default;
        virtual Base* Clone() const = 0;
        virtual const std::type_info& Type() const = 0;
    };

    template <typename T>
    struct Derived : public Base {
        explicit Derived(const T& value) : value_(value) {
        }
        Base* Clone() const override {
            return new Derived<T>(value_);
        }
        const std::type_info& Type() const override {
            return typeid(T);
        }
        T value_;
    };

private:
    Base* data_;

public:
    Any() : data_(nullptr) {
    }

    template <class T>
    explicit Any(const T& value) : data_(new Derived<T>(value)) {
    }

    template <class T>
    Any& operator=(const T& value) {
        Any(value).Swap(*this);
        return *this;
    }
    Any(const Any& rhs) : data_(rhs.data_ ? rhs.data_->Clone() : nullptr) {
    }

    Any& operator=(Any rhs) {
        rhs.Swap(*this);
        return *this;
    }

    ~Any() {
        Clear();
    }

    bool Empty() const {
        return data_ == nullptr;
    }

    void Clear() {
        delete data_;
        data_ = nullptr;
    }

    void Swap(Any& rhs) {
        std::swap(data_, rhs.data_);
    }
    template <class T>
    const T& GetValue() const {
        if (!data_ || data_->Type() != typeid(T)) {
            throw std::bad_cast();
        }
        return dynamic_cast<Derived<T>*>(data_)->value_;
    }
};