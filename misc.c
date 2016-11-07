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
  int linear_index = random_location();
  int y = linear_index / 4;
  int x = linear_index % 4;
  data[y][x] = 2;
  linear_index = random_location();
  y = linear_index / 4;
  x = linear_index % 4;
  data[y][x] = 2;
  show(start_y, start_x);
}

// return a random location (0-15) in data table which is 0
int random_location() {
  int index = 0;
  int count = 0;

  while (index++ <= 15) 
    if (data[index / 4][index % 4] == 0)
      count++;
  
  int empty_location[count];
  memset(empty_location, 0, sizeof empty_location);
  index = 0;
  int empty_index = 0;
  
  while (index <= 15){
    if (data[index/4][index%4] == 0) {
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
    for(int x=0; x<4; x++) {
	  int linear_index = 4*y+x;
	  int vy = linear_index / 4;
	  int vx = linear_index % 4;
	  mvprintw(start_y+2+y*4, start_x+2+x*7, "%d", data[vy][vx]);	
	}
}

int my_random() {
  srand(time(NULL));
  return rand();
}

void run(int start_y, int start_x) {
  int key;
  while((key = getch()) != 'q') {
    switch(key) {
      case KEY_UP:
      case 'w':
      case 'W':
        up();
        break;
      case KEY_DOWN:
      case 's':
      case 'S':
        down();
        break;
      case KEY_LEFT:
      case 'a':
      case 'A':
        left();
        break;
      case KEY_RIGHT:
      case 'd':
      case 'D':
        right();
        break;
    }
    show(start_y, start_x);
    refresh();
  }
}

void up_remove_blank() {
	for(int x=0; x<4; x++) {
		for(int i=0; i<3; i++) {
			for(int y=1; y<4; y++) {
				if (data[y-1][x] == 0 && data[y][x] != 0) {
					int temp = data[y-1][x];
					data[y-1][x] = data[y][x];
					data[y][x] = temp;
				}
			}
		}
	}
}

void down_remove_blank() {
	for(int x=0; x<4; x++ ) { // 四竖排中的每一竖
		for(int i=0; i<3; i++ ){  // 每一竖都需要三次才能检查完毕
			for(int y=2; y>=0; y--) { // 每一竖从第三个开始检查, 如果下面的为零，而自己不为0，则交换两者的位置。
			  if (data[y+1][x] == 0 && data[y][x] != 0) {
				  int temp = data[y+1][x];
				  data[y+1][x] = data[y][x];
				  data[y][x] = temp;
			  }
			}
		}
	}
}



void left_remove_blank() {
  	for(int y=0; y<4; y++) {
		for(int i=0; i<3; i++) {
			for(int x=1; x<4; x++) {
				if (data[y][x-1] == 0 && data[y][x] != 0) {
					int temp = data[y][x-1];
					data[y][x-1] = data[y][x];
					data[y][x] = temp;
				}
			}
		}
	}
}

void right_remove_blank() {
	for(int y=0; y<4; y++) {
		for (int i=0; i<3; i++) {
			for(int x=2; x>=0; x-- ) {
				if(data[y][x+1] == 0 && data[y][x] != 0) {
					int temp = data[y][x+1];
                    data[y][x+1] = data[y][x];
					data[y][x] = temp;
				}
			}
		}
	}
}

void up() {
	up_remove_blank();
	for(int x=0; x<4; x++) {
		if (data[0][x] == data[1][x]) {
			data[0][x] *= 2;
			data[1][x] = 0;
			if(data[2][x] == data[3][x]) {
				data[2][x] *= 2;
				data[3][x] = 0;
			}
		} else if ( data[1][x] == data[2][x]) {
			data[1][x] *= 2;
			data[2][x] = 0;
		} else if (data[2][x] == data[3][x]) {
			data[2][x] *= 2;
			data[3][x] = 0;
		}
	}
	up_remove_blank();
}

void  down() {
	down_remove_blank();
	//合并相邻相同
	for(int x=0; x<4; x++) {
		if (data[3][x] == data[2][x]) {
			data[3][x] *= 2;
			data[2][x] = 0;
			if (data[1][x] == data[0][x]) {
				data[1][x] *= 2;
				data[0][x] = 0;
			}
		} else if (data[2][x] == data[1][x]) {
			data[2][x] *= 2;
			data[1][x] = 0;
		} else if (data[1][x] == data[0][x]){
			data[1][x] *=2;
			data[0][x] = 0;
		}
	}
	down_remove_blank();
}

void left() {
	left_remove_blank();
	for(int y=0; y<4; y++) {
		if (data[y][0] == data[y][1]) {
			data[y][0] *= 2;
			data[y][1] = 0;
			if(data[y][2] == data[y][3]) {
				data[y][2] *= 2;
				data[y][3] = 0;
			}
		} else if (data[y][1] == data[y][2]) {
			data[y][1] *= 2;
			data[y][2] = 0;
		} else if (data[y][2] == data[y][3]) {
			data[y][2] *= 2;
			data[y][3] = 0;
		}
	}
	left_remove_blank();
}

void right() {
	right_remove_blank();
	for(int y=0; y<4; y++) {
		if(data[y][3] == data[y][2]) {
			data[y][3] *= 2;
			data[y][2] = 0;
			if(data[y][1] == data[y][0]) {
				data[y][1] *= 2;
				data[y][0] = 0;
			}
		} else if (data[y][2] == data[y][1]) {
			data[y][2] *= 2;
			data[y][1] = 0;
		} else if (data[y][1] == data[y][0]) {
			data[y][1] *= 2;
			data[y][0] = 0;
		}
	}
	right_remove_blank();
}

bool add_a_digit() {
	
}