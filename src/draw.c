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
  if (x < 0 || y < UPPER_PADDING || x >= board->w || y >= board->h + UPPER_PADDING)
    return;

  drect(
      x * SCALE + board->x,
      (y - UPPER_PADDING) * SCALE + board->y,
      x * SCALE + board->x + SCALE - 1,
      (y - UPPER_PADDING) * SCALE + board->y + SCALE - 1,
      C_BLACK);

  dpixel(
    x * SCALE + board->x + 1,
    (y - UPPER_PADDING) * SCALE + board->y + 1,
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
  for (int y = UPPER_PADDING; y < board->h + UPPER_PADDING; y++) {
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

void draw_game_over(const Game *game) {
  int window_h = 40;
  int window_w = 100;
  drect_border(
      SCREEN_WIDTH/2 - window_w/2,
      SCREEN_HEIGHT/2 - window_h/2,
      SCREEN_WIDTH/2 + window_w/2,
      SCREEN_HEIGHT/2 + window_h/2,
      C_WHITE, 1, C_BLACK);

  dtext_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 5, C_BLACK, C_WHITE, DTEXT_CENTER, DTEXT_CENTER, "GAME OVER!");
  dprint_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 5, C_BLACK, C_WHITE, DTEXT_CENTER, DTEXT_CENTER, "score: %d", game->score);

}

void draw_menu()
{
  extern bopti_image_t img_title; 
  dclear(C_WHITE);
  dimage(0, 0, &img_title);
  dtext_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 13, C_BLACK, C_WHITE, DTEXT_CENTER, DTEXT_CENTER, "Press any key");
  dtext_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 23, C_BLACK, C_WHITE, DTEXT_CENTER, DTEXT_CENTER, "to start!");
}