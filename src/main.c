#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/timer.h>
#include <gint/clock.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include "draw.h"

static int get_inputs();
static int callback_tick(volatile int *tick);

static void start_game();

static void game_loop(Game *game);
static void on_piece_drop(Game *game);

static volatile int tick = 1;

static Board board = {
  .w = BOARD_WIDTH,
  .h = BOARD_HEIGHT,
  .x = (SCREEN_WIDTH / 2) - (10 / 2 * SCALE),
  .y = (SCREEN_HEIGHT / 2) - (20 / 2 * SCALE)
};
static bool data[BOARD_WIDTH * (BOARD_HEIGHT + UPPER_PADDING)];
static Tet curr_tet;
static Game game;

int main()
{
  // Setup
  extern font_t better_font;
  extern bopti_image_t img_logo;
  srand(time(NULL));
  dfont(&better_font);

  dclear(C_WHITE);
  dtext_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 13, C_BLACK, C_WHITE, DTEXT_CENTER, DTEXT_CENTER, "Produced by the one and only");
  dimage(22, SCREEN_HEIGHT/2 - 7, &img_logo);
  dupdate();
  getkey();

  // Configure timer
  int t = timer_configure(TIMER_ANY, ENGINE_TICK * 1000, GINT_CALL(callback_tick, &tick));
  if (t >= 0) {
    timer_start(t);
  }
  else {
    return 0;
  }

  game.state = MENU;

  int flashingText = 500;
  int timeout = 1;
  bool showFlashingText = true;

  while(1) {
    while (!tick)
      sleep();
    tick = 0;

    if(game.state == GAME) {

      game_loop(&game);
    } else if(game.state == MENU) {
      draw_menu();
      flashingText -= ENGINE_TICK;

      key_event_t ev = getkey_opt(GETKEY_DEFAULT, &timeout);
      if (ev.type != KEYEV_NONE)
        start_game();

      if(flashingText <= 0) {
        draw_menu_flashing_text(showFlashingText);
        showFlashingText = !showFlashingText;
        flashingText = 500;
        dupdate();
      }

    }
  }

  if (t >= 0)
    timer_stop(t);

  return 0;
}

static void start_game() {
  // Init objects
  memset(data, false, board.w * (board.h + UPPER_PADDING)); // clear board
  board.data = data;

  game.alive = true,
  game.score = 0,
  game.drop_duration = 750,
  game.next_tet = get_random_tet(),
  game.board = &board,
  game.curr_tet = &curr_tet,
  game.level = 1,
  game.lines_cleared = 0,

  spawn_next_tet(&game);

  // Draw initial stuff
  dclear(C_WHITE);
  draw_board_borders(&board);
  draw_board(&board, &curr_tet);
  draw_ui(&game);
  dupdate();

  game.state = GAME;
}

static void game_loop(Game *game) {
  if(!game->alive) {
    draw_game_over(game);
    dupdate();

    sleep_ms(1500);
    clearevents();
    getkey();

    game->state = MENU;
    return;
  }
  // Get user input
  int dir = get_inputs();

  //Movement
  if (dir >= ACTION_DOWN && dir <= ACTION_LEFT) {
    move_tet(game, dir);

  }
  if (dir == ACTION_ROTATE) {
    rotate_tet(game);
  }

  if (dir == ACTION_HARDDROP) {
    hard_drop(game);
    on_piece_drop(game); // instantly cause piece to drop
  }

  bool hit = apply_gravity(game);

  if(!hit){
    on_piece_drop(game);
  }

  // Update screen
  draw_board(game->board, game->curr_tet);
  dupdate();
}


static void on_piece_drop(Game *game) {
  add_tet_to_board(game);
  spawn_next_tet(game);
  draw_ui(game);
}

static int get_inputs(void) {
  int opt = GETKEY_DEFAULT;
  int timeout = 1;

  while (1)
  {
    key_event_t ev = getkey_opt(opt, &timeout);
    if (ev.type == KEYEV_NONE)
      return -1;

    int key = ev.key;
    if (key == KEY_RIGHT)
      return ACTION_RIGHT;
    if (key == KEY_LEFT)
      return ACTION_LEFT;
    if (key == KEY_DOWN)
      return ACTION_DOWN;
    if (key == KEY_0)
      return ACTION_ROTATE;
    if (key == KEY_DOT)
      return ACTION_HARDDROP;
  }
}

static int callback_tick(volatile int *tick) {
  *tick = 1;
  return TIMER_CONTINUE;
}
