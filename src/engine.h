#ifndef _TETRIS_ENGINE_H
#define _TETRIS_ENGINE_H

/* Directions */
#define DIR_DOWN 0
#define DIR_RIGHT 1
#define DIR_UP 2
#define DIR_LEFT 3


/* Blocks */
#define SHAPE_L 0
#define SHAPE_J 1
#define SHAPE_S 2
#define SHAPE_Z 3
#define SHAPE_T 4
#define SHAPE_O 5
#define SHAPE_I 6

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SCALE 3

typedef struct  {
  int block;
  int x, y;
  int rotation;
} Block;


typedef struct {
  int w, h;
} Board;


typedef struct {
  int score;
  Block *curr_block;
  Board *board;
} Game;

void move_block(Game *game, int dir);
void draw_board_borders(const Game *game);
void draw_board(Game *game);


#endif /* _TETRIS_ENGINE_H */
