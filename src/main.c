#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/timer.h>
#include <gint/clock.h>
#include "engine.h"
#include "draw.h"

static void draw_menu();
static int get_inputs();
static int callback_tick(volatile int *tick);


int main()
{
  draw_menu();
  dupdate();
  getkey();


  // Configure timer
  static volatile int tick = 1;
  int t = timer_configure(TIMER_ANY, ENGINE_TICK * 1000, GINT_CALL(callback_tick, &tick));
  if (t >= 0) {
    timer_start(t);
  }
  else {
    return 1;
  }

  // Init objects
  Board board = { 
    .w = BOARD_WIDTH, 
    .h = BOARD_HEIGHT, 
    .x = (SCREEN_WIDTH / 2) - (10 / 2 * SCALE), 
    .y = (SCREEN_HEIGHT / 2) - (20 / 2 * SCALE)
  };
  bool data[board.w * board.h];
  for(int i = 0; i < board.w * board.h; i++) {
      data[i] = false;
  }
  board.data = data;

  Tet curr_tet = { 
    .x = 0, 
    .y = 0, 
    .tet = get_random_tet()
  };

  Game game = { 
    .score = 0, 
    .drop_duration = 350,

    .board = &board, 
    .curr_tet = &curr_tet
  };


  // Draw initial stuff
  draw_board_borders(&board);
  draw_board(&board, &curr_tet);
  dupdate();

  // Main update loop
  while (1)
  {
    while (!tick)
      sleep();
    tick = 0;

    // Get user input
    int dir = get_inputs();
    
    //Movement
    if (dir >= ACTION_DOWN && dir <= ACTION_LEFT) {
      move_tet(&game, dir);
    } 
    if (dir == ACTION_ROTATE) {
      rotate_tet(&game);
    }

    engine_update(&game);

    // Update screen
    draw_board(&board, &curr_tet);
    dupdate();
  }

  if (t >= 0)
    timer_stop(t);
  return 1;
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
  }
}

static void draw_menu()
{
  dclear(C_WHITE);
  dtext(1, 1, C_BLACK, "TETRIS GAME!");
  dtext(1, 9, C_BLACK, "Press any key");
  dtext(1, 18, C_BLACK, "to start!");
}

static int callback_tick(volatile int *tick)
{
  *tick = 1;
  return TIMER_CONTINUE;
}