#include <gint/display.h>
#include <gint/clock.h>
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

  dtext_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 5, C_BLACK, C_WHITE, DTEXT_CENTER, DTEXT_MIDDLE, "GAME OVER!");
  dprint_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 5, C_BLACK, C_WHITE, DTEXT_CENTER, DTEXT_MIDDLE, "score: %d", game->score);

}

void draw_ui(const Game *game) {
  int next_tet_x = game->board->x + game->board->w * SCALE + 5;
  int next_tet_y = 3;
  dtext(next_tet_x, next_tet_y, C_BLACK, "next:");
  dimage(next_tet_x + 2, next_tet_y + 7, tetrominos[game->next_tet].img);

  int score_x = 5;
  int score_y = 3;
  dtext(score_x, score_y, C_BLACK, "score:");
  drect(score_x + 2, score_y + 7, game->board->x - 2, score_y + 20, C_WHITE);
  dprint(score_x + 2, score_y + 7, C_BLACK, "%d", game->score);

  int level_x = 5;
  int level_y = 33;
  dtext(level_x, level_y, C_BLACK, "level:");
  drect(level_x + 2, level_y + 7, game->board->x - 2, level_y + 20, C_WHITE);
  dprint(level_x + 2, level_y + 7, C_BLACK, "%d", game->level);
}

void draw_menu() {
  extern bopti_image_t img_title;
  dclear(C_WHITE);
  dimage(0, 0, &img_title);
}

void draw_menu_flashing_text(bool show) {
  if (show == true) {
    dtext_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 12, C_BLACK, C_WHITE, DTEXT_CENTER, DTEXT_MIDDLE, "Press any key");
    dtext_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 22, C_BLACK, C_WHITE, DTEXT_CENTER, DTEXT_MIDDLE, "to start!");
  } else {
    dtext_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 12, C_WHITE, C_WHITE, DTEXT_CENTER, DTEXT_MIDDLE, "Press any key");
    dtext_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 22, C_WHITE, C_WHITE, DTEXT_CENTER, DTEXT_MIDDLE, "to start!");
  }
}

void level_up_animation(int level, volatile int *tick) {
  int blackX = -SCREEN_WIDTH * 2;
  while(blackX < SCREEN_WIDTH) {
    while (!*tick)
      sleep();
    *tick = 0;

    blackX += 10;
    dclear(C_WHITE);
    drect(blackX, 0, blackX + (SCREEN_WIDTH * 2) - 1, SCREEN_HEIGHT - 1, C_BLACK);
    dprint_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, C_WHITE, C_NONE, DTEXT_CENTER, DTEXT_MIDDLE, "LEVEL %d", level);
    dupdate();
  }
}

void redraw_game(const Game *game) {
  draw_board_borders(game->board);
  draw_board(game->board, game->curr_tet);
  draw_ui(game);
}
