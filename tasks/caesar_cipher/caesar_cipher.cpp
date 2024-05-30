#include "caesar_cipher.h"

std::string Decipher(const std::string& cipher, size_t shift) {
    std::string answer;
    const int start_alphabet = 65;
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (uint64_t i = 0; i < cipher.size(); ++i) {
        if ((static_cast<int>(cipher[i]) - start_alphabet - static_cast<int>(shift)) >= 0) {
            answer += alphabet[static_cast<int>(cipher[i]) - start_alphabet - static_cast<int>(shift)];
        } else {
            answer +=
                alphabet[static_cast<int>(cipher[i]) - start_alphabet - static_cast<int>(shift) + alphabet.size()];
        }
    }
    return answer;
}
