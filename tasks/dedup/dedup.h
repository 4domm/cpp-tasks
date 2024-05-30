#pragma once
#include <vector>

#include "memory"
template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> result;
    result.reserve(items.size());
    for (const auto& item : items) {
        result.push_back(std::make_unique<T>(*item));
    }
    return result;
}
template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::vector<std::shared_ptr<T>> result;
    for (auto& item : items) {
        auto iter = std::find_if(result.begin(), result.end(),
                                 [&item](const std::shared_ptr<T>& other) -> bool { return *other == *item; });
        if (iter == result.end()) {
            result.push_back(std::make_shared<T>(*item));
        } else {
            std::shared_ptr<T>& other = *iter;
            result.push_back(other);
        }
    }
    return result;
}
