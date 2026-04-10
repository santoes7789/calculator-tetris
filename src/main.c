#include <gint/display.h>
#include <gint/keyboard.h>
#include "engine.h"

static void draw_menu();
static int get_inputs();

int main() {
  draw_menu();
  dupdate();
  getkey();

  // init basic thingies
  Board board = {.w = 10, .h = 20};

  Block curr_block = {
    .block = SHAPE_L,
    .x = 60,
    .y = 20,
    .rotation = 0
  };

  Game game = {
    .board = &board,
    .score = 0, 
    .curr_block = &curr_block
  };


  draw_board_borders(&game);
  draw_board(&game);
  dupdate();

  while (1) {
    draw_board(&game);
    dupdate();
    int dir = get_inputs();
    move_block(&game, dir);
  }
  


  return 1;
}

static int get_inputs() {
  int opt = GETKEY_DEFAULT & ~GETKEY_REP_ARROWS;
  while(1) {
    int key = getkey_opt(opt, NULL).key;
    if (key == KEY_RIGHT) return DIR_RIGHT;
    if (key == KEY_LEFT) return DIR_LEFT;
  }
}

static void draw_menu() {
  dclear(C_WHITE);
  dtext(1, 1, C_BLACK, "TETRIS GAME!");
  dtext(1, 9, C_BLACK, "Press any key");
  dtext(1, 18, C_BLACK, "to start!");
}
