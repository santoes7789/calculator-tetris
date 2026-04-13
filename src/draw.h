#ifndef _DRAW_H_
#define _DRAW_H_ 
#include "engine.h"

void clear_board(const Board *board);
void draw_block(int x, int y, const Board *board);
void draw_board(const Board *board, const Tet *tet);
void draw_board_borders(const Board *board);
void draw_next_tet(int x, int y, bopti_image_t *img);

void draw_game_over();
void draw_menu();

#endif /* _DRAW_H_ */