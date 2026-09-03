#ifndef _DRAW_H_
#define _DRAW_H_
#include "engine.h"

void clear_board(const Board *board);
void draw_block(int x, int y, const Board *board);
void draw_board(const Board *board, const Tet *tet);
void draw_board_borders(const Board *board);
void draw_score(const Game *game);
void draw_update_score(const Game *game);
void draw_next_tet(const Game*game);
void draw_level(const Game *game);
void draw_menu_flashing_text(bool show);
void draw_game_over();
void draw_menu();
void level_up_animation(int level, volatile int *tick);
void draw_full_screen(const Game *game);

#endif /* _DRAW_H_ */
