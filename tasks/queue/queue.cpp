#include "queue.h"
Node::Node(int32_t value, Node* next) : value(value), next(next) {
}
Queue::Queue() : front_(nullptr), tail_(nullptr), size_(0) {
}
Queue::~Queue() {
    Clear();
}
void Queue::Push(int32_t value) {
    Node* new_node = new Node(value, nullptr);
    if (Empty()) {
        front_ = new_node;
        tail_ = new_node;
    } else {
        tail_->next = new_node;
        tail_ = new_node;
    }
    ++size_;
}
void Queue::Pop() {
    if (!Empty()) {
        Node* node_remove = front_;
        front_ = front_->next;
        delete node_remove;
        --size_;
        if (Empty()) {
            tail_ = nullptr;
        }
    }
}
int32_t Queue::Front() const {
    return front_->value;
}
int32_t Queue::Size() const {
    return size_;
}
void Queue::Clear() {
    while (!Empty()) {
        Pop();
    }
    size_ = 0;
}
bool Queue::Empty() const {
    return size_ == 0;
}
