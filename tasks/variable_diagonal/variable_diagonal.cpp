#include "variable_diagonal.h"

#include <cstdint>

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int** array = new int*[lines];
    for (size_t i = 0; i < lines; ++i) {
        array[i] = new int[columns];
    }
    int value = 0;
    uint64_t line = 0;
    int64_t col = 0;
    for (size_t i = 0; i < columns; ++i) {
        col = static_cast<int64_t>(i);
        line = 0;
        while (col != -1 && line != lines) {
            array[line][col] = value++;
            line += 1;
            col -= 1;
        }
    }
    for (size_t j = 1; j < lines; ++j) {
        col = static_cast<int64_t>(columns) - 1;
        line = j;
        while (line != lines && col != -1) {
            array[line][col] = value++;
            line += 1;
            col -= 1;
        }
    }
    return array;
}