/*************************************************************************
 * File    : move.h
 * Author  : Quan Zhuo <zhuo.quan@outlook.com>
 * Purpose : contains function and macro declaration
 * Created : Sun 06 Nov 2016 05:55:20 PM CST
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

#include <stdbool.h>

#include <stdio.h>

#define TABLE_HEIGHT 17
#define TABLE_LENGTH 29

extern int data[4][4];
extern int start_y, start_x;

void init_table();
int random_location();
void show();
void run();
int my_random();
void process(int key);
void up_remove_blank();
void down_remove_blank();
void left_remove_blank();
void right_remove_blank();
bool up();
bool down();
bool left();
bool right();
void insert_a_digit();
bool changed(int (*)[4], int (*)[4]);
void copy_arr(int (*)[4], int (*)[4]);
void print();
bool can_move();
