#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    int current_value = 0;
    int current_line = 0;
    int current_column = 0;
    for (int i = 0; i < COLUMNS; ++i) {
        current_column = i;
        current_line = 0;
        while (current_column != -1 && current_line != LINES) {
            table[current_line][current_column] = current_value++;
            current_line += 1;
            current_column -= 1;
        }
    }
    for (int j = 1; j < LINES; ++j) {
        current_column = COLUMNS - 1;
        current_line = j;
        while (current_line != LINES && current_column != -1) {
            table[current_line][current_column] = current_value++;
            current_line += 1;
            current_column -= 1;
        }
    }
}
