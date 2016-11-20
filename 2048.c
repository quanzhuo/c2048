#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <stdio.h>
#include "move.h"

int data[4][4] = {0};
int start_y, start_x;

int main(int argc, char **argv) {  
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
  
  init_table();
  
  refresh();
  keypad(stdscr, true);
  run();
  
  endwin();
  exit(EXIT_SUCCESS);
 }

 
 void run() {
  int key;
  while ((key = getch()) != 'q') {
    switch (key) {
    case KEY_UP:
    case 'w':
    case 'W':
      if (up())
        insert_a_digit();
      break;
    case KEY_DOWN:
    case 's':
    case 'S':
      if (down())
        insert_a_digit();
      break;
    case KEY_LEFT:
    case 'a':
    case 'A':
      if (left())
        insert_a_digit();
      break;
    case KEY_RIGHT:
    case 'd':
    case 'D':
      if (right())
        insert_a_digit();
      break;
    }
	erase();
    show();
    refresh();
  }
}