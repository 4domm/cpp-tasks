#include "cppstring.h"

#include "cstring"
String::String() : size_(0), capacity_(0), data_(nullptr) {
}
String::String(size_t size, char symbol) : size_(size), capacity_(size * 2), data_(nullptr) {
    if (capacity_ != 0) {
        data_ = new char[capacity_];
        for (size_t i = 0; i < size; ++i) {
            data_[i] = symbol;
        }
    }
}
String::String(const char *src) : size_(0), capacity_(0), data_(nullptr) {  // NOLINT
    if (src != nullptr && strlen(src) != 0) {
        size_ = strlen(src);
        capacity_ = size_ * 2;
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = src[i];
        }
    }
}
String::String(const char *src, size_t size) : size_(size), capacity_(size * 2), data_(new char[capacity_]) {
    for (size_t i = 0; i < size; ++i) {
        data_[i] = src[i];
    }
}
String::~String() {
    delete[] data_;
}
String::String(const String &other) : size_(other.size_), capacity_(size_ * 2), data_(nullptr) {
    if (capacity_ != 0) {
        data_ = new char[capacity_];
        for (size_t i = 0; i < other.size_; ++i) {
            data_[i] = other[i];
        }
    }
}
String &String::operator=(const String &other) {
    if (this != &other) {
        if (other.data_) {
            delete[] data_;
            data_ = new char[other.size_ * 2];
            for (size_t i = 0; i < other.size_; ++i) {
                data_[i] = other[i];
            }
            size_ = other.size_;
            capacity_ = other.size_ * 2;
        } else {
            delete[] data_;
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }
    }
    return *this;
}
const char &String::operator[](size_t idx) const {
    return data_[idx];
}
char &String::operator[](size_t idx) {
    return data_[idx];
}
const char &String::At(size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return data_[idx];
}
char &String::At(size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange();
    }
    return data_[idx];
}
const char &String::Front() const {
    return data_[0];
}
char &String::Front() {
    return data_[0];
}
const char &String::Back() const {
    return data_[size_ - 1];
}
char &String::Back() {
    return data_[size_ - 1];
}
const char *String::Data() const {
    return data_;
}
char *String::Data() {
    return data_;
}
const char *String::CStr() const {
    return data_;
}
char *String::CStr() {
    return data_;
}
bool String::Empty() const {
    return size_ == 0;
}
size_t String::Size() const {
    return size_;
}
size_t String::Length() const {
    return size_;
}
size_t String::Capacity() const {
    return capacity_;
}
void String::Clear() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}
void String::Swap(String &other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}
void String::PopBack() {
    --size_;
}
void String::PushBack(char c) {
    if (size_ + 1 >= capacity_) {
        char *new_data = new char[(size_ + 1) * 2];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = (size_ + 1) * 2;
    }
    data_[size_] = c;
    ++size_;
}
void String::Resize(size_t new_size, char symbol) {
    if (new_size <= size_) {
        size_ = new_size;
    } else {
        size_t current_size = size_;
        size_ = new_size;
        if (new_size > capacity_) {
            char *new_data = new char[new_size * 2];
            if (data_) {
                for (size_t i = 0; i < size_; ++i) {
                    new_data[i] = data_[i];
                }
                delete[] data_;
            }
            data_ = new_data;
            capacity_ = new_size * 2;
        }
        for (size_t i = current_size; i < new_size; ++i) {
            data_[i] = symbol;
        }
    }
}
void String::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        char *new_data = new char[new_capacity];
        if (data_) {
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = new_capacity;
    }
}
void String::ShrinkToFit() {
    if (size_ < capacity_) {
        char *new_data = new char[size_];
        if (data_) {
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = size_;
    }
}
int String::Compare(const String &other) const {
    for (size_t i = 0; i < std::min(other.size_, size_); ++i) {
        if (data_[i] < other.data_[i]) {
            return -1;
        } else if (data_[i] > other.data_[i]) {
            return 1;
        }
    }
    if (size_ > other.size_) {
        return 1;
    } else if (size_ < other.size_) {
        return -1;
    }
    return 0;
}

String &String::operator+=(const String &other) {
    if (other.size_ + size_ >= capacity_) {
        char *new_data = new char[(other.size_ + size_ + 1) * 2];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        for (size_t i = 0; i < other.size_; ++i) {
            new_data[size_ + i] = other[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = (other.size_ + size_ + 1) * 2;
    } else {
        for (size_t i = 0; i < other.size_; ++i) {
            data_[size_ + i] = other[i];
        }
    }
    size_ = other.size_ + size_;
    return *this;
}
String operator+(const String &first, const String &second) {
    String result;
    result.size_ = first.size_ + second.size_;
    result.capacity_ = (first.size_ + second.size_) * 2;
    result.data_ = new char[result.capacity_];
    for (size_t i = 0; i < first.size_; ++i) {
        result[i] = first[i];
    }
    for (size_t i = 0; i < second.size_; ++i) {
        result[i + first.size_] = second[i];
    }
    return result;
}
std::ostream &operator<<(std::ostream &stream, const String &string) {
    for (size_t i = 0; i < string.Size(); ++i) {
        stream << string[i];
    }
    return stream;
}
bool operator==(const String &first, const String &second) {
    return first.Compare(second) == 0;
}
bool operator!=(const String &first, const String &second) {
    return first.Compare(second) != 0;
}
bool operator>(const String &first, const String &second) {
    return first.Compare(second) > 0;
}
bool operator<(const String &first, const String &second) {
    return first.Compare(second) < 0;
}
bool operator>=(const String &first, const String &second) {
    return first.Compare(second) >= 0;
}
bool operator<=(const String &first, const String &second) {
    return first.Compare(second) <= 0;
}
void SafeCpy(char *dest, const char *src, size_t len) {
    strncpy(dest, src, len);
}