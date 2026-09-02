#ifndef _DRAW_H_
#define _DRAW_H_
#include "engine.h"

void clear_board(const Board *board);
void draw_block(int x, int y, const Board *board);
void draw_board(const Board *board, const Tet *tet);
void draw_board_borders(const Board *board);
void draw_ui(const Game *game);
void draw_menu_flashing_text(bool show);
void draw_game_over();
void draw_menu();

#endif /* _DRAW_H_ */
