#include <stdbool.h>
#include "tetrominos.h"

const TetData tetrominos[7] = {
    [0] = {.size = 3, .data = {true, true, true, true, false, false, false, false, false, false, false, false}}, // L
    [1] = {.size = 3, .data = {true, true, true, false, false, true, false, false, false, false, false, false}}, // J
    [2] = {.size = 3, .data = {false, true, true, true, true, false, false, false, false, false, false, false}}, // S
    [3] = {.size = 3, .data = {true, true, false, false, true, true, false, false, false, false, false, false}}, // Z
    [4] = {.size = 3, .data = {true, true, true, false, true, false, false, false, false, false, false, false}}, // T
    [5] = {.size = 3, .data = {true, true, false, true, true, false, false, false, false, false, false, false}}, // O
    [6] = {.size = 4, .data = {true, true, true, true, false, false, false, false, false, false, false, false}} // L
};