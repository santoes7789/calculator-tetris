#include <gint/display.h>
#include "draw.h"
#include "engine.h"

void clear_board(const Board *board) {
  drect(
      board->x,
      board->y,
      board->x + board->w * SCALE - 1,
      board->y + board->h * SCALE - 1, C_WHITE);
}

void draw_block(int x, int y, const Board *board) {
  if (x < 0 || y < 0 || x >= board->w || y >= board->h)
    return;

  drect(
      x * SCALE + board->x,
      y * SCALE + board->y,
      x * SCALE + board->x + SCALE - 1,
      y * SCALE + board->y + SCALE - 1,
      C_BLACK);

  dpixel(
    x * SCALE + board->x + 1,
    y * SCALE + board->y + 1,
    C_WHITE);
}

void draw_board(const Board *board, const Tet *tet) {
  clear_board(board);

  // Draw the active block
  int index = 0;
  for (int dy = 0; dy < tet->tet.size; dy++) {
    for (int dx = 0; dx < tet->tet.size; dx++) {
      if (get_i_block(tet, index)) {
        draw_block(tet->x + dx, tet->y + dy, board);
      }
      index++;
    }
  }

  // Draw rest of the board
  for (int y = 0; y < board->h; y++) {
    for (int x = 0; x < board->w; x++) {
      if (board->data[x + (y * board->w)]) {
        draw_block(x, y, board);
      }
    }
  }
}

void draw_board_borders(const Board *board) {
  dclear(C_WHITE);
  drect_border(
      board->x - 1,
      board->y - 1,
      board->x + board->w * SCALE,
      board->y + board->h * SCALE,
      C_WHITE, 1, C_BLACK);
}