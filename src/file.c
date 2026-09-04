#include <stdio.h>

const char *fileName = "tetris.txt";

void save_highscore(int score) {
  FILE *file = fopen(fileName, "w");
  if (file == NULL) {
    return;
  }

  fprintf(file, "%d", score);
  fclose(file);
}

int load_highscore() {
  int highscore;

  FILE *file = fopen(fileName, "r");
  if (file == NULL) {
    return 0;
  }
  if (fscanf(file, "%d", &highscore) != 1)
      highscore = 0;

  fclose(file);
  return highscore;
}
