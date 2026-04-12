#include <gint/display.h>
#include <stdlib.h>
#include "engine.h"
#include "tetrominos.h"

TetData get_random_tet() {
  int r = rand() % 7;
  return tetrominos[r];
}

int y_spawn = -2;
void spawn_new_tet(Game * game) {
  game->curr_tet->y = y_spawn;
  game->curr_tet->tet = get_random_tet(); 
}

void clear_board(const Board *board) {
  drect(
    board->x, 
    board->y, 
    board->x + board->w * SCALE - 1, 
    board->y + board->h * SCALE - 1, C_WHITE);
}

void draw_block(int x, int y, const Board *board) {
  if(x < 0 || y < 0 || x >= board->w || y >= board->h) return;

  drect(
    x*SCALE + board->x,
    y*SCALE + board->y,
    x*SCALE + board->x + SCALE - 1,
    y*SCALE + board->y + SCALE - 1,
    C_BLACK
   );
}

void draw_board(const Board *board, const Tet *tet) {
  clear_board(board);
  
  // Draw the active block
  int index = 0;
  for(int dy = 0; dy < tet->tet.size; dy++) {
    for(int dx = 0; dx < tet->tet.size; dx++) {
      if(tet->tet.data[index]) {
        draw_block(tet->x + dx, tet->y + dy, board);
      }
      index++;
    }
  }

  // Draw rest of the board
  for(int y = 0; y < board->h; y++) {
    for(int x = 0; x < board->w; x++) {
      if(board->data[x + (y * board->w)]) {
        draw_block(x, y, board);
      }
    }
  }

}

void draw_board_borders(const Board *board) {
  dclear(C_WHITE);
  drect_border(
    board->x - 1, 
    board->y - 1, 
    board->x + board->w * SCALE, 
    board->y + board->h * SCALE, 
    C_WHITE, 1, C_BLACK);
}


// Checks whether the tet moved by dx and dy will collide with anything
bool check_collision(const Tet *tet, const Board *board, int dx, int dy) {
  int index = 0;
  for(int y = 0; y < tet->tet.size; y++) {
    for(int x = 0; x < tet->tet.size; x++) { 
      if(!tet->tet.data[index]) {
        index++;
        continue;
      }


      int board_x = tet->x + x + dx;
      int board_y = tet->y + y + dy;

      // Checking borders
      if(board_x < 0 ||
         board_x >= board->w || 
         board_y >= board->h ) {
          return true;
         }

      // Checking board
      if(board_y >=0 && board->data[board_x + (board_y * board->w)]) {
        return true;
      }

      index++;
    }
  }

  return false;
}

void add_tet_to_board(const Tet *tet, Board *board) {
  int index = 0;

  for(int y = 0; y < tet->tet.size; y++) {
    for(int x = 0; x < tet->tet.size; x++) { 
      if(tet->tet.data[index]) {
        int board_x = tet->x + x;
        int board_y = tet->y + y;
        board->data[board_x + (board_y * board->w)] = true;
      }
      index++;
    }
  }
}

void move_tet(Game *game, int dir) {
  int dx = (dir == DIR_RIGHT) - (dir == DIR_LEFT);
  int dy = (dir == DIR_DOWN) - (dir == DIR_UP);
  
  if(check_collision(game->curr_tet, game->board, dx, dy)) {
    if(dy) {
      add_tet_to_board(game->curr_tet, game->board);
      spawn_new_tet(game);
    }
  } else {
    game->curr_tet->x += dx;
    game->curr_tet->y += dy;
  }
}


// void rotate_tet(Game *game, int dir) {
// }


void engine_update(Game *game) {
  // Gravity
  game->curr_tet->drop_duration -= ENGINE_TICK;
  if (game->curr_tet->drop_duration <= 0) {
    move_tet(game, DIR_DOWN);
    game->curr_tet->drop_duration = game->drop_duration;
  }
}