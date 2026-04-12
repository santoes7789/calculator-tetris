#include "engine.h"

void clear_board(const Board *board);
void draw_block(int x, int y, const Board *board);
void draw_board(const Board *board, const Tet *tet);
void draw_board_borders(const Board *board);

void draw_game_over();
void draw_menu();