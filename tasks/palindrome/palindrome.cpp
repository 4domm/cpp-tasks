#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    int64_t left = 0;
    int64_t right = static_cast<int64_t>(str.size()) - 1;
    while (left < right) {
        if (str[left] == ' ') {
            left += 1;
        } else if (str[right] == ' ') {
            right -= 1;
        } else if (str[left] != str[right]) {
            return false;
        } else {
            left += 1;
            right -= 1;
        }
    }
    return true;
}
