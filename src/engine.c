#include <gint/display.h>
#include <stdlib.h>
#include "engine.h"
#include "tetrominos.h"

// Order in which blocks should be read if rotated 90 degrees
static const int s_three_rotated[9] = {6, 3, 0, 7, 4, 1, 8, 5, 2};
static const int s_four_rotated[16] = {12, 8, 4, 0, 13, 9, 5, 1, 14, 10, 6, 2, 15, 11, 7, 3};

bool get_i_block(const Tet *tet, int index) {
  int i;
  if (tet->rotation == 0){
    i = index;

  } else if (tet->rotation == 2){
    i = (tet->tet.size * tet->tet.size) - 1 - index;

  } else if (tet->tet.size == 3){

    if (tet->rotation == 1){
      i = s_three_rotated[index];
    } else {
      i = s_three_rotated[8 - index];
    }

  } else {
    if (tet->rotation == 1) {
      i = s_four_rotated[index];
    } else {
      i = s_four_rotated[15 - index];
    }
  }

  return tet->tet.data[i];
}

TetData get_random_tet() {
  int r = rand() % 7;
  return tetrominos[r];
}

void spawn_new_tet(Game *game) {
  int y_spawn = 0;
  int x_spawn = game->board->w/2 - 1;
  game->curr_tet->tet = get_random_tet();
  game->curr_tet->y = y_spawn;
  game->curr_tet->x = x_spawn;
  game->curr_tet->rotation = 0;

  if(check_collision(game->curr_tet, game->board, 0, 0, 0)){
    game->alive = false;
  }
}


// Checks whether the tet moved by dx and dy will collide with anything
bool check_collision(const Tet *tet, const Board *board, int dx, int dy, int dr) {
  int index = 0;

  // Create another tet with the transformations applied
  Tet copied_tet = *tet;
  copied_tet.x += dx;
  copied_tet.y += dy;
  copied_tet.rotation = (copied_tet.rotation + dr) % 4;

  for (int y = 0; y < tet->tet.size; y++) {
    for (int x = 0; x < tet->tet.size; x++) {
      if (!get_i_block(&copied_tet, index)) {
        index++;
        continue;
      }

      int board_x = copied_tet.x + x;
      int board_y = copied_tet.y + y;

      // Checking borders
      if (board_x < 0 ||
          board_x >= board->w ||
          board_y >= (board->h + UPPER_PADDING)) {
        return true;
      }

      // Checking board
      if (board_y >= 0 && board->data[board_x + (board_y * board->w)]) {
        return true;
      }

      index++;
    }
  }

  return false;
}

void add_tet_to_board(Game *game) {
  int index = 0;

  for (int y = 0; y < game->curr_tet->tet.size; y++) {
    for (int x = 0; x < game->curr_tet->tet.size; x++) {
      if (get_i_block(game->curr_tet, index)) {
        int board_x = game->curr_tet->x + x;
        int board_y = game->curr_tet->y + y;
        game->board->data[board_x + (board_y * game->board->w)] = true;
      }
      index++;
    }
  }
  clear_full_lines(game);
}

void clear_line(int y, Game *game) {
  for(int x = 0; x < game->board->w; x++) {
    game->board->data[x + (y * game->board->w)] = false;
  }
  for(int i = y; i > 0; i--) {
    for(int x = 0; x < game->board->w; x++) {
      game->board->data[x + (i * game->board->w)] = game->board->data[x + ((i - 1) * game->board->w)];
    }
  }
  for(int x = 0; x < game->board->w; x++) {
    game->board->data[x] = false;
    game->score += LINE_PTS;
  }
}

void clear_full_lines(Game *game) {
  for(int y = 0; y < game->board->h + UPPER_PADDING; y++) {
    bool clear = true;
    for(int x = 0; x < game->board->w; x++) {
      if(!game->board->data[x + (y * game->board->w)]) {
        clear = false;
        break;
      }
    }

    if(clear) {
      clear_line(y, game);
    }
  }
}

bool move_tet(Game *game, int dir) {
  int dx = (dir == ACTION_RIGHT) - (dir == ACTION_LEFT);
  int dy = (dir == ACTION_DOWN);

  if (check_collision(game->curr_tet, game->board, dx, dy, 0)) {
    if (dy) {
      add_tet_to_board(game);
      spawn_new_tet(game);
    }
    return false;
  }
  else {
    game->curr_tet->x += dx;
    game->curr_tet->y += dy;
    return true;
  }
}

void hard_drop(Game *game) {
  int count;
  while(move_tet(game, ACTION_DOWN)){
    //Break if it reaches infinite loop
    if(count > game->board->h*2) {
      break;
    }
  }

}

void rotate_tet(Game *game) {
  if (game->curr_tet->tet.name == SHAPE_O)
    return;
  
  if(!check_collision(game->curr_tet, game->board, 0, 0, 1)) {
    game->curr_tet->rotation = (game->curr_tet->rotation + 1) % 4;
  }
}

void engine_update(Game *game) {
  // Gravity
  game->curr_tet->drop_duration -= ENGINE_TICK;
  if (game->curr_tet->drop_duration <= 0) {
    move_tet(game, ACTION_DOWN);
    game->curr_tet->drop_duration = game->drop_duration;
  }
}