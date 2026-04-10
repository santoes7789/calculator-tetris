#include <gint/display.h>
#include "engine.h"

void clear_board(const Game *game) {
  Board *board = game->board;
  int x = (SCREEN_WIDTH/2) - (board->w/2 * SCALE) - 1;
  int y = (SCREEN_HEIGHT/2) - (board->h/2 * SCALE) - 1;
  drect(x + 1, y + 1, x + board->w * SCALE, y + board->h * SCALE, C_WHITE);

}
void draw_board(Game *game) {
  clear_board(game);
  dpixel(game->curr_block->x, game->curr_block->y, C_BLACK);
}

void move_block(Game *game, int dir) {
  int dx = (dir == DIR_RIGHT) - (dir == DIR_LEFT);
  game->curr_block->x += dx;
}

void draw_board_borders(const Game *game) {
  Board *board = game->board;
  dclear(C_WHITE);
  int x = (SCREEN_WIDTH/2) - (board->w/2 * SCALE) - 1;
  int y = (SCREEN_HEIGHT/2) - (board->h/2 * SCALE) - 1;
  drect_border(x, y, x + board->w * SCALE + 1, y + board->h * SCALE + 1, C_WHITE, 1, C_BLACK);
}
