# 
#   File    : Makefile
#   Author  : Quan Zhuo <zhuo.quan@outlook.com>
#   Purpose : for gnu make
#   Created : Sun Nov  6 16:36:08 CST 2016
#     
#   This program is free software; you can redistribute it and/or
#   modify it under the terms of the GNU General Public License as
#   published by the Free Software Foundation; either version 2 of the
#   License, or (at your option) any later version.
#  
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   General Public License for more details.
#  
#   You should have received a copy of the GNU General Public License along
#   with this program; if not, write to the Free Software Foundation, Inc.,
#   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
# 

CFLAGS := -std=c99

objects := $(patsubst %.c, %.o, $(wildcard *.c))

all: c2048

c2048: $(objects)
	gcc -o c2048 $^ -lncurses

$(objects): %.o: %.c
	gcc -c $(CFLAGS) $< -o $@ -lncurses

.PHONY: clean

clean:
	-rm -rf *.o \
	rm -rf c2048

.PHONY: install

install: c2048
	@if [ ! -d ~/bin ]; then \
	  mkdir ~/bin ;\
	else \
	  cp c2048 ~/bin/ ;\
	  echo "Installed in ~/bin successfully !" ;\
	fi

.PHONY: uninsall

uninstall:
	-rm -rf  ~/bin/c2048
