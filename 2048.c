#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include "misc.h"

int data[4][4] = {0};
FILE *log_file = NULL;

int main(int argc, char **argv) {
  int start_x, start_y, len_x, len_y;
  
  initscr();

  if (LINES-1 < TABLE_HEIGHT || COLS - 1 < TABLE_LENGTH) {
    fprintf(stderr,"This game require a terminal that is %d "\
	    "in length and %d in height at least !\n",
	    TABLE_LENGTH, TABLE_HEIGHT);
    endwin();
    exit(EXIT_FAILURE);
  }

  noecho();
  start_x = (COLS - TABLE_LENGTH) / 2;
  start_y = (LINES - TABLE_HEIGHT) / 2;

  init_table(start_y, start_x);
  log_file = fopen(".move_log", "w+");
  refresh();
  run(start_y, start_x);
  
  fclose(log_file);
  endwin();
  exit(EXIT_SUCCESS);
 }
