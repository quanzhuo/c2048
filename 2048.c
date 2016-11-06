#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

int main(int argc, char **argv) {
  
  initscr();
  
  printw("lines: %d\ncolums: %d", LINES, COLS);

  refresh();

  sleep(10);
  
  endwin();
  exit(EXIT_SUCCESS);
 }
