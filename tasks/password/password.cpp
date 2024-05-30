#include "password.h"

bool ValidatePassword(const std::string& password) {
    const int min_len = 8;
    const int max_len = 14;
    const int min_ascii = 33;
    const int max_ascii = 126;
    int special_chars = 0;
    int big_letters = 0;
    int small_letters = 0;
    int numbers = 0;
    if (password.size() < min_len || password.size() > max_len) {
        return false;
    }
    for (uint64_t i = 0; i < password.size(); ++i) {
        if (static_cast<int>(password[i]) < min_ascii || static_cast<int>(password[i]) > max_ascii) {
            return false;
        } else if (std::isupper(password[i])) {
            big_letters = 1;
        } else if (std::islower(password[i])) {
            small_letters = 1;
        } else if (std::isdigit(password[i])) {
            numbers = 1;
        } else if (std::isgraph(password[i])) {
            special_chars = 1;
        }
    }
    return numbers + big_letters + small_letters + special_chars >= 3;
}
