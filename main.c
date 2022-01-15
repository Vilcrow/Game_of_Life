/*
Game of Life

Copyright (C) 2022 S.V.I 'Vilcrow', <svi@vilcrow.net>
--------------------------------------------------------------------------------
LICENCE:
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------------------
*/
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "carriage.h"
#include "cell.h"

void start_curses_mode()
{
	initscr();
	if(!has_colors()) {
		endwin();
		fprintf(stderr, _("Your terminal don't support colors\n"));
		exit(1);	
	}
	cbreak();
	keypad(stdscr, 1);
	noecho();
	start_color();
}

int main(int argc, char **argv)
{
	char is_quit_game = 0;	/*stay in the game*/
	int cur_y = 0;
	int cur_x = 0;
	int row, col;
	int c;
	enum key_value kv;
	cell *cell_zero = NULL;
	cell *cell_next = NULL;
	start_curses_mode();
	getmaxyx(stdscr, row, col);
	while(!is_quit_game) {
		c = getch();
		kv = check_key(c);
		switch(kv) {
		case mv:
			move_carriage(row, col, c, &cur_y, &cur_x);
			break;
		case add:
			if(!is_in_list(cell_zero, cur_y, cur_x)) {
				add_alive_cell(&cell_zero, cur_y, cur_x);
				show_cell(cur_y, cur_x);
			}
			else {
				rm_cell(&cell_zero, cur_y, cur_x);
				hide_cell(cur_y, cur_x);
			}
			break;
		case finish:
			if(cell_zero == NULL) {
				mvaddstr(row-1, 1, _("Initial conditions aren't set"));
				move(cur_y, cur_x);
			}
			else
				;
			break;
		case esc:
			endwin();
			return 0;
		default:
			mvaddch(1, 1, '*');
			break;
		}
	}
	endwin();
	return 0;
}
