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
  Board board = {
    .w = 10, 
    .h = 20,
    .x = (SCREEN_WIDTH/2) - (10/2 * SCALE),
    .y = (SCREEN_HEIGHT/2) - (20/2 * SCALE)
  };

  Tet curr_tet = {
    .x = 0,
    .y = 0,
  };

  Game game = {
    .board = &board,
    .score = 0, 
    .curr_tet = &curr_tet
  };


  draw_board_borders(&board);
  draw_board(&game);
  dupdate();

  while (1) {
    draw_board(&game);
    dupdate();
    int dir = get_inputs();
    move_tet(&game, dir);
  }
  


  return 1;
}

static int get_inputs() {
  int opt = GETKEY_DEFAULT;
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
