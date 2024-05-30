#include "word2vec.h"

#include <limits>
#include <vector>
int ScalarProd(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    int result = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        result += vec1[i] * vec2[i];
    }
    return result;
}
std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    std::vector<std::string> closest_words;
    int max_prod = std::numeric_limits<int>::min();
    for (size_t i = 1; i < words.size(); ++i) {
        if (ScalarProd(vectors[0], vectors[i]) > max_prod) {
            closest_words.clear();
            closest_words.emplace_back(words[i]);
            max_prod = ScalarProd(vectors[0], vectors[i]);
        } else if (ScalarProd(vectors[0], vectors[i]) == max_prod) {
            closest_words.emplace_back(words[i]);
        }
    }
    return closest_words;
}
