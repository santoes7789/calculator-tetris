#include <gint/display.h>
#include <stdlib.h>
#include "engine.h"
#include "tetrominos.h"



#include <gint/keyboard.h>

void clear_board(const Board *board) {
  drect(
    board->x, 
    board->y, 
    board->x + board->w * SCALE - 1, 
    board->y + board->h * SCALE - 1, C_WHITE);

}

void draw_block(int x, int y, const Board *board) {
  if(x < 0 || y < 0 || x >= board->w || y >= board->h) return;

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
  int index = 0;
  for(int dy = 0; dy < game->curr_tet->tet.size; dy++) {
    for(int dx = 0; dx < game->curr_tet->tet.size; dx++) {
      if(game->curr_tet->tet.data[index]) {
        draw_block(game->curr_tet->x + dx, game->curr_tet->y + dy, game->board);
      }
      index++;
    }
  }
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
