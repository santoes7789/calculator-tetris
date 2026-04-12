#ifndef _TETRIS_ENGINE_H
#define _TETRIS_ENGINE_H

#include "tetrominos.h"

#define ENGINE_TICK 25

/* Actions */
#define ACTION_DOWN 0
#define ACTION_RIGHT 1
#define ACTION_LEFT 2

#define ACTION_HARDDROP 3
#define ACTION_ROTATE 4

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

#define SCALE 3


typedef struct  {
  TetData tet;
  int x, y;
  int rotation;
  int drop_duration;
} Tet;


typedef struct {
  int w, h;
  int x, y;
  bool *data;
} Board;


typedef struct {
  int score;
  int drop_duration;
  Tet *curr_tet;
  Board *board;
} Game;


bool get_i_block(const Tet *tet, int index);
TetData get_random_tet();
void spawn_new_tet(Game *game);
bool check_collision(const Tet *tet, const Board *board, int dx, int dy, int dr);

void add_tet_to_board(const Tet *tet, Board *board);
void move_tet(Game *game, int dir);
void rotate_tet(Game *game);
void engine_update(Game *game);

#endif /* _TETRIS_ENGINE_H */
