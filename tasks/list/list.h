#pragma once
#include <cstddef>

#include "utility"
template <class T>
class ListNode {

public:
    explicit ListNode(T&& value) : value_(std::move(value)) {
    }

    explicit ListNode(const T& value) : value_(value) {
    }

    ~ListNode() {
        next_ = nullptr;
        previous_ = nullptr;
    }

    T& GetValue() {
        return value_;
    }

    ListNode<T>* next_ = nullptr;
    ListNode<T>* previous_ = nullptr;
    T value_;
};
template <typename T>
class List {
public:
    class Iterator {
    private:
        ListNode<T>* current_;
        size_t index_;

    public:
        Iterator(ListNode<T>* current, size_t pos) : current_(current), index_(pos) {
        }

        Iterator operator++() {
            current_ = current_->next_;
            ++index_;
            return Iterator(current_, index_);
        }

        Iterator operator++(int) {
            Iterator res(current_, index_);
            current_ = current_->next_;
            ++index_;
            return res;
        }

        Iterator operator--() {

            current_ = current_->previous_;
            --index_;
            return Iterator(current_, index_);
        }
        Iterator operator--(int) {
            Iterator res(current_, index_);
            --index_;
            current_ = current_->previous_;
            return res;
        }

        T& operator*() const {
            return current_->GetValue();
        }

        T* operator->() const {
            return &(current_->GetValue());
        }

        bool operator==(const Iterator& rhs) const {
            return rhs.index_ == index_;
        }
        bool operator!=(const Iterator& rhs) const {
            return rhs.index_ != index_;
        }
    };

    List() {
        front_ = nullptr;
        back_ = front_;
        size_ = 0;
    }

    void AddFirst(T&& value) {
        front_ = new ListNode<T>(std::forward<T>(value));
        front_->next_ = front_;
        front_->previous_ = front_;
        back_ = front_;
        ++size_;
    }

    void AddFirst(const T& value) {
        front_ = new ListNode<T>(value);
        front_->next_ = front_;
        front_->previous_ = front_;
        back_ = front_;
        ++size_;
    }

    void Clear() {
        while (!IsEmpty()) {
            PopBack();
        }
        delete front_;
    }

    List(const List& list) : List() {
        ListNode<T>* node = list.front_;
        while (size_ < list.size_) {
            PushBack(node->GetValue());
            node = node->next_;
        }
    }

    List(List&& list) : List() {
        front_ = list.front_;
        back_ = list.back_;
        size_ = list.size_;
        list.front_ = nullptr;
        list.back_ = nullptr;
        list.size_ = 0;
        list.Clear();
    }

    ~List() {
        Clear();
    }

    List& operator=(const List& list) {
        Clear();
        ListNode<T>* node = list.front_;
        while (size_ < list.size_) {
            PushBack(node->GetValue());
            node = node->next_;
        }
        return *this;
    }

    List& operator=(List&& list) {
        Clear();
        front_ = list.front_;
        back_ = list.back_;
        size_ = list.size_;
        list.front_ = nullptr;
        list.back_ = nullptr;
        list.size_ = 0;
        return *this;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

    size_t Size() const {
        return size_;
    }

    void PushBack(T&& elem) {
        if (size_ == 0) {
            AddFirst(std::forward<T>(elem));
        } else {
            ListNode<T>* node = new ListNode<T>(std::forward<T>(elem));
            node->previous_ = back_;
            node->next_ = front_;
            back_->next_ = node;
            front_->previous_ = node;
            back_ = node;
            size_++;
        }
    }

    void PushBack(const T& elem) {
        if (size_ == 0) {
            AddFirst(elem);
        } else {
            ListNode<T>* node = new ListNode<T>(elem);
            node->previous_ = back_;
            node->next_ = front_;
            back_->next_ = node;
            front_->previous_ = node;
            back_ = node;
            size_++;
        }
    }

    void PushFront(T&& elem) {
        if (size_ == 0) {
            AddFirst(std::forward<T>(elem));
        } else {
            ListNode<T>* node = new ListNode<T>(std::forward<T>(elem));
            node->next_ = front_;
            node->previous_ = back_;
            front_->previous_ = node;
            back_->next_ = node;
            front_ = node;
            size_++;
        }
    }

    void PushFront(const T& elem) {
        if (size_ == 0) {
            AddFirst(elem);
        } else {
            ListNode<T>* node = new ListNode<T>(elem);
            node->next_ = front_;
            node->previous_ = back_;
            front_->previous_ = node;
            back_->next_ = node;
            front_ = node;
            ++size_;
        }
    }

    T& Front() {
        return front_->GetValue();
    }
    const T& Front() const {
        return front_->GetValue();
    }
    T& Back() {
        return back_->GetValue();
    }
    const T& Back() const {
        return back_->GetValue();
    }

    void PopBack() {
        if (size_ > 1) {
            ListNode<T>* new_back = back_->previous_;
            front_->previous_ = new_back;
            new_back->next_ = front_;
            delete back_;
            back_ = new_back;
            size_--;
        } else {
            front_ = nullptr;
            delete back_;
            size_--;
        }
    }
    void PopFront() {
        if (size_ > 1) {
            ListNode<T>* new_front = front_->next_;
            new_front->previous_ = back_;
            back_->next_ = new_front;
            delete front_;
            front_ = new_front;
            size_--;
        } else {
            back_ = nullptr;
            delete front_;
            size_--;
        }
    }
    Iterator Begin() {
        return Iterator(front_, 0);
    }
    Iterator End() {
        return Iterator(back_, size_);
    }

    Iterator begin() {  // NOLINT
        return Begin();
    }
    Iterator end() {  // NOLINT
        return End();
    }

private:
    ListNode<T>* front_;
    ListNode<T>* back_;
    size_t size_ = 0;
};

template <typename T>
typename List<T>::Iterator begin(const List<T>& list) {  // NOLINT
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(const List<T>& list) {  // NOLINT
    return list.End();
}
