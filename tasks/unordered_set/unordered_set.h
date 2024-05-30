#pragma once
#include <list>
#include <utility>
#include <vector>

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet() : count_(0), data_(1) {
    }

    explicit UnorderedSet(size_t count) : count_(0), data_(count) {
    }
    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last) : count_(0) {
        size_t dist = std::distance(first, last);
        data_.resize(dist == 0 ? 1 : dist);
        for (auto it = first; it != last; ++it) {
            Insert(*it);
        }
    }

    UnorderedSet(const UnorderedSet& other) : count_(other.count_), data_(other.data_) {
    }

    UnorderedSet(UnorderedSet&& other) : count_(std::exchange(other.count_, 0)), data_(std::move(other.data_)) {
        other.data_.clear();
        other.data_.resize(1);
    }

    UnorderedSet& operator=(const UnorderedSet& other) {
        if (this != &other) {
            count_ = other.count_;
            data_ = other.data_;
        }
        return *this;
    }
    UnorderedSet& operator=(UnorderedSet&& other) noexcept {
        if (this != &other) {
            count_ = std::exchange(other.count_, 0);
            data_ = std::move(other.data_);
            other.data_.clear();
            other.data_.resize(1);
        }
        return *this;
    }

    ~UnorderedSet() = default;

    size_t Size() const {
        return count_;
    }
    bool Empty() const {
        return count_ == 0;
    }
    void Clear() {
        for (auto& bucket : data_) {
            bucket.clear();
        }
        count_ = 0;
    }
    void Insert(const KeyT& key) {
        size_t bucket_idx = GetIndex(key);
        std::list<KeyT>& bucket = data_[bucket_idx];
        if (std::find(bucket.begin(), bucket.end(), key) != bucket.end()) {
            return;
        }
        bucket.push_back(key);
        ++count_;
        if (LoadFactor() > 1.0) {
            Rehash(data_.size() * 2);
        }
    }

    void Insert(KeyT&& key) {
        size_t bucket_idx = GetIndex(key);
        std::list<KeyT>& bucket = data_[bucket_idx];
        if (std::find(bucket.begin(), bucket.end(), key) != bucket.end()) {
            return;
        }
        bucket.push_back(std::move(key));
        ++count_;
        if (LoadFactor() > 1.0) {
            Rehash(data_.size() * 2);
        }
    }
    void Erase(const KeyT& key) {
        size_t bucket_idx = GetIndex(key);
        std::list<KeyT>& bucket = data_[bucket_idx];
        bucket.erase(std::remove(bucket.begin(), bucket.end(), key), bucket.end());
        --count_;
    }
    bool Find(const KeyT& key) const {
        size_t bucket_idx = GetIndex(key);
        const std::list<KeyT>& bucket = data_[bucket_idx];
        return std::find(bucket.begin(), bucket.end(), key) != bucket.end();
    }

    void Rehash(size_t new_bucket_count) {
        if (new_bucket_count == data_.size() || new_bucket_count < count_) {
            return;
        }
        std::vector<std::list<KeyT>> new_data(new_bucket_count);
        for (auto& bucket : data_) {
            for (const KeyT& elem : bucket) {
                size_t id = std::hash<KeyT>{}(elem) % new_data.size();
                new_data[id].push_back(elem);
            }
        }
        data_ = std::move(new_data);
    }

    void Reserve(size_t new_bucket_count) {
        if (new_bucket_count > data_.size()) {
            Rehash(new_bucket_count);
        }
    }
    size_t BucketCount() const {
        if (data_.size() == 1 && count_ == 0) {
            return 0;
        }
        return data_.size();
    }
    size_t BucketSize(size_t id) const {
        if (id < data_.size()) {
            return data_[id].size();
        }
        return 0;
    }
    size_t Bucket(const KeyT& key) const {
        return GetIndex(key);
    }
    double LoadFactor() const {
        if (data_.empty()) {
            return 0.0;
        }
        return static_cast<double>(count_) / data_.size();
    }

private:
    size_t count_;
    std::vector<std::list<KeyT>> data_;
    size_t GetIndex(const KeyT& key) const {
        return std::hash<KeyT>{}(key) % data_.size();
    }
    size_t GetIndex(const KeyT& key, size_t bucket_count) const {
        return std::hash<KeyT>{}(key) % bucket_count;
    }
};