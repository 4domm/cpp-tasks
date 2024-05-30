#include "cstring.h"
size_t Strlen(const char* str) {
    size_t str_len = 0;
    while (*str) {
        ++str_len;
        ++str;
    }
    return str_len;
}
int Strcmp(const char* first, const char* second) {
    while (*second && (*first == *second)) {
        ++first;
        ++second;
    }
    return static_cast<int>(static_cast<unsigned char>(*first)) - static_cast<int>(static_cast<unsigned char>(*second));
}
int Strncmp(const char* first, const char* second, size_t count) {
    while (count--) {
        if (*first && *second && *first == *second) {
            ++first;
            ++second;
        } else {
            return static_cast<int>(static_cast<unsigned char>(*first)) -
                   static_cast<int>(static_cast<unsigned char>(*second));
        }
    }
    return 0;
}
char* Strcpy(char* dest, const char* src) {
    char* temp_dest = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = *src;
    return temp_dest;
}
char* Strncpy(char* dest, const char* src, size_t count) {
    char* temp_dest = dest;
    while (count && *src) {
        --count;
        *dest++ = *src++;
    }
    if (count) {
        while (count--) {
            *dest++ = '\0';
        }
    }
    return temp_dest;
}
char* Strcat(char* dest, const char* src) {
    char* temp_dest = dest;
    while (*dest) {
        ++dest;
    }
    while (*src) {
        *dest++ = *src++;
    }
    *dest = *src;
    return temp_dest;
}
char* Strncat(char* dest, const char* src, size_t count) {
    char* temp_dest = dest;
    while (*dest) {
        ++dest;
    }
    while (count-- && *src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return temp_dest;
}
const char* Strchr(const char* str, char symbol) {
    while (*str) {
        if (*str == symbol) {
            return str;
        }
        ++str;
    }
    if (*str == symbol) {
        return str;
    }
    return nullptr;
}
const char* Strrchr(const char* str, char symbol) {
    const char* last = nullptr;
    while (*str) {
        if (*str == symbol) {
            last = str;
        }
        ++str;
    }
    if (*str == symbol) {
        return str;
    }
    return last;
}
size_t Strspn(const char* dest, const char* src) {
    size_t count = 0;
    while (*dest && Strchr(src, *dest++)) {
        ++count;
    }
    return count;
}
size_t Strcspn(const char* dest, const char* src) {
    size_t count = 0;
    while (*dest && !Strchr(src, *dest++)) {
        ++count;
    }
    return count;
}
const char* Strpbrk(const char* dest, const char* breakset) {
    while (*dest) {
        if (Strchr(breakset, *dest)) {
            return dest;
        }
        ++dest;
    }
    return nullptr;
}
const char* Strstr(const char* str, const char* pattern) {
    if (*pattern == '\0') {
        return str;
    }
    while (*str) {
        const char* current_str = str;
        const char* current_pattern = pattern;
        while (*current_pattern && *current_str == *current_pattern) {
            ++current_str;
            ++current_pattern;
        }
        if (!*current_pattern) {
            return str;
        }
        ++str;
    }
    return nullptr;
}