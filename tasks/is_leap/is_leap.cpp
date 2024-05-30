#include "is_leap.h"

bool IsLeap(int year) {
    const int a = 100;
    const int b = 400;
    if ((year % 4 == 0 && year % a != 0) || year % b == 0) {
        return true;
    }
    return false;
}
