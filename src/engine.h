#ifndef _TETRIS_ENGINE_H
#define _TETRIS_ENGINE_H

#include "tetrominos.h"

#define ENGINE_TICK 25

/* Directions */
#define DIR_DOWN 0
#define DIR_RIGHT 1
#define DIR_UP 2
#define DIR_LEFT 3

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SCALE 3

typedef struct  {
  TetData tet;
  int x, y;
  int drop_duration;
} Tet;


typedef struct {
  int w, h;
  int x, y;
  bool *data;
} Board;


typedef struct {
  int score;
  Tet *curr_tet;
  Board *board;
} Game;

void move_tet(Game *game, int dir);
void draw_board_borders(const Board *board);
void draw_board(Game *game);
void get_random_tet(TetData *tet); 


#endif /* _TETRIS_ENGINE_H */
