#include <gint/display.h>
#include <stdlib.h>
#include "engine.h"
#include "tetrominos.h"

void clear_board(const Board *board) {
  drect(
    board->x, 
    board->y, 
    board->x + board->w * SCALE - 1, 
    board->y + board->h * SCALE - 1, C_WHITE);

}

void draw_block(int x, int y, const Board *board) {
  drect(
    x*SCALE + board->x,
    y*SCALE + board->y,
    x*SCALE + board->x + SCALE - 1,
    y*SCALE + board->y + SCALE - 1,
    C_BLACK
   );
}

void draw_board(Game *game) {
  clear_board(game->board);
  
  //2 steps, draw the active block, and then all the 'dead' blocks'
  draw_block(game->curr_tet->x, game->curr_tet->y, game->board);
}

void move_tet(Game *game, int dir) {
  int dx = (dir == DIR_RIGHT) - (dir == DIR_LEFT);
  game->curr_tet->x += dx;
}

// void rotate_tet(Game *game, int dir) {
// }

void draw_board_borders(const Board *board) {
  dclear(C_WHITE);
  drect_border(
    board->x - 1, 
    board->y - 1, 
    board->x + board->w * SCALE, 
    board->y + board->h * SCALE, 
    C_WHITE, 1, C_BLACK);
}

void get_random_tet(TetData *tet) {
  int r = rand() & 7;
  *tet = tetrominos[r];
}
