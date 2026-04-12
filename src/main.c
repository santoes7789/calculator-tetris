#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/timer.h>
#include <gint/clock.h>
#include "engine.h"
#include "draw.h"

static int get_inputs();
static int callback_tick(volatile int *tick);
static void start_game();

int main()
{
  while(1) {
    draw_menu();
    dupdate();
    getkey();
    start_game();
  }

  return 0;
}

static void start_game() {
  // Configure timer
  static volatile int tick = 1;
  int t = timer_configure(TIMER_ANY, ENGINE_TICK * 1000, GINT_CALL(callback_tick, &tick));
  if (t >= 0) {
    timer_start(t);
  }
  else {
    return;
  }

  // Init objects
  Board board = { 
    .w = BOARD_WIDTH, 
    .h = BOARD_HEIGHT, 
    .x = (SCREEN_WIDTH / 2) - (10 / 2 * SCALE), 
    .y = (SCREEN_HEIGHT / 2) - (20 / 2 * SCALE)
  };
  bool data[board.w * (board.h + UPPER_PADDING)];
  for(int i = 0; i < board.w * (board.h + UPPER_PADDING); i++) {
      data[i] = false;
  }
  board.data = data;

  Tet curr_tet;
  Game game = { 
    .alive = true,
    .score = 0, 
    .drop_duration = 350,

    .board = &board, 
    .curr_tet = &curr_tet
  };

  spawn_new_tet(&game);

  // Draw initial stuff
  draw_board_borders(&board);
  draw_board(&board, &curr_tet);
  dupdate();

  // Main update loop
  while (1) {
    while (!tick)
      sleep();
    tick = 0;

    if(!game.alive) {
      draw_game_over(&game);
      dupdate();
      break;
    } 
    // Get user input
    int dir = get_inputs();
    
    //Movement
    if (dir >= ACTION_DOWN && dir <= ACTION_LEFT) {
      move_tet(&game, dir);
    } 
    if (dir == ACTION_ROTATE) {
      rotate_tet(&game);
    }

    if (dir == ACTION_HARDDROP) {
      hard_drop(&game);
    }

    engine_update(&game);

    // Update screen
    draw_board(&board, &curr_tet);
    dupdate();
    
  }
  if (t >= 0)
    timer_stop(t);
  getkey();
}

static int get_inputs(void)
{
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

static int callback_tick(volatile int *tick)
{
  *tick = 1;
  return TIMER_CONTINUE;
}