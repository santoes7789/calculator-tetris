#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/timer.h>
#include <gint/clock.h>
#include "engine.h"

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

  // Initilization
  int drop_duration = 1000;
  Board board = { .w = 10, .h = 20, .x = (SCREEN_WIDTH / 2) - (10 / 2 * SCALE), .y = (SCREEN_HEIGHT / 2) - (20 / 2 * SCALE)};
  Tet curr_tet = { .x = 2, .y = 2, .drop_duration = drop_duration};
  get_random_tet(&curr_tet.tet);
  Game game = { .board = &board, .score = 0, .curr_tet = &curr_tet};


  // Draw initial stuff
  draw_board_borders(&board);
  draw_board(&game);
  dupdate();

  while (1)
  {
    while (!tick)
      sleep();
    tick = 0;

    draw_board(&game);
    dupdate();

    int dir = get_inputs();
    if (dir >= 0) {
      move_tet(&game, dir);
    }

    curr_tet.drop_duration -= ENGINE_TICK;
    if(curr_tet.drop_duration <= 0) {
      move_tet(&game, DIR_DOWN);
      curr_tet.drop_duration = drop_duration;
    }
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
      return DIR_RIGHT;
    if (key == KEY_LEFT)
      return DIR_LEFT;
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