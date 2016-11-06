/*************************************************************************
 * File    : misc.c
 * Author  : Quan Zhuo <zhuo.quan@outlook.com>
 * Purpose : 一些杂七杂八的辅助函数 
 * Created : Sun 06 Nov 2016 05:54:47 PM CST 
 *   
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *************************************************************************
 */

#include "misc.h"
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <time.h>

void init_table(int start_y, int start_x) {
  data[random_location(data)] = 2;
  data[random_location(data)] = 2;
  show(start_y, start_x);
}

// return a random location (0-15) in data table which is empty
int random_location(int *ptr) {
  int index = 0;
  int count = 0;

  while (index++ <= 15) 
    if (ptr[index] == 0)
      count++;
  
  int empty_location[count];
  memset(empty_location, 0, sizeof empty_location);
  index = 0;
  int empty_index = 0;
  
  while (index <= 15){
    if (ptr[index] == 0) {
      empty_location[empty_index] = index;
      empty_index++;
    }
    index++;
  }
  
  return empty_location[my_random() % count];
}

void show(int start_y, int start_x) {
  // draw h-lines
  for(int i=0; i<5; i++)
    mvhline(start_y + i*4, start_x, '-', TABLE_LENGTH);

  // draw v-lines
  for(int i=0; i<5; i++)
    mvvline(start_y, start_x + i*7, '|', TABLE_HEIGHT);

  // draw digit
  for(int y=0; y<4; y++)
    for(int x=0; x<4; x++) 
      mvprintw(start_y+2+y*4, start_x+2+x*7, "%d", data[4*y+x]);
}

int my_random() {
  srand(time(NULL));
  return rand();
}

void run(int start_y, int start_x) {
  int key;
  key = getch();
  while(key != ERR && key != 'q') {
    switch(key) {
      case KEY_UP:
      case 'w':
      case 'W':
        process('w');
        break;
      case KEY_DOWN:
      case 's':
      case 'S':
        process('s');
        break;
      case KEY_LEFT:
      case 'a':
      case 'A':
        process('a');
        break;
      case KEY_RIGHT:
      case 'd':
      case 'D':
        process('d');
        break;
    }
    show(start_y, start_x);
    refresh();
  }
}

void process(int key) {
  
}




































