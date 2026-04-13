#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/timer.h>
#include <gint/clock.h>
#include "engine.h"
#include "draw.h"

static int get_inputs();
static int callback_tick(volatile int *tick);
static void start_game();
static void on_piece_drop(Game * game);

int main()
{
  extern font_t better_font;
  extern bopti_image_t img_logo; 
  


  dfont(&better_font); 

  dclear(C_WHITE);
  dtext_opt(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 13, C_BLACK, C_WHITE, DTEXT_CENTER, DTEXT_CENTER, "Produced by the one and only");
  dimage(22, SCREEN_HEIGHT/2 - 7, &img_logo);
  dupdate();
  getkey();

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
    .next_tet = get_random_tet(),

    .board = &board, 
    .curr_tet = &curr_tet
  };

  spawn_next_tet(&game);


  // Draw initial stuff
  dclear(C_WHITE);
  draw_board_borders(&board);
  int next_tet_x = board.x + board.w * SCALE + 5;
  int next_tet_y = 3;
  draw_next_tet(next_tet_x, next_tet_y, tetrominos[game.next_tet].img);
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
      on_piece_drop(&game);
    }

    if(!apply_gravity(&game)){
      on_piece_drop(&game);
    }

    // Update screen
    draw_board(&board, &curr_tet);
    dupdate();
    
  }
  if (t >= 0)
    timer_stop(t);
  getkey();
}

static void on_piece_drop(Game *game) {
  add_tet_to_board(game);
  spawn_next_tet(game);
  draw_next_tet(game->board->x + game->board->w * SCALE + 5, 3, tetrominos[game->next_tet].img);
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