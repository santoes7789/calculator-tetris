#include <stdbool.h>
#include "tetrominos.h"

const TetData tetrominos[7] = {
    [0] = {
        .size = 3, 
        .name = SHAPE_L, 
        .img = &img_L_piece,
        .data = {false, false, true, true, true, true, false, false, false, false, false, false}},

    [1] = {
        .size = 3, 
        .name = SHAPE_J, 
        .img = &img_J_piece,
        .data = {true, false, false, true, true, true, false, false, false, false, false, false}}, // J

    [2] = {
        .size = 3, 
        .name = SHAPE_S, 
        .img = &img_S_piece,
        .data = {false, true, true, true, true, false, false, false, false, false, false, false}}, // S

    [3] = {
        .size = 3, 
        .name = SHAPE_Z, 
        .img = &img_Z_piece,
        .data = {true, true, false, false, true, true, false, false, false, false, false, false}}, // Z

    [4] = {
        .size = 3, 
        .name = SHAPE_T, 
        .img = &img_T_piece,
        .data = {false, true, false, true, true, true, false, false, false, false, false, false}}, // T

    [5] = {
        .size = 3, 
        .name = SHAPE_O, 
        .img = &img_O_piece,
        .data = {true, true, false, true, true, false, false, false, false, false, false, false}}, // O

    [6] = {
        .size = 4, 
        .name = SHAPE_I, 
        .img = &img_I_piece,
        .data = {false, false, false, false, true, true, true, true, false, false, false, false}} // I
};