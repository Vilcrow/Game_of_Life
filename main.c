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
#include "preparation.h"
#include "msgbox.h"
#include "renderer.h"

void start_curses_mode()
{
	initscr();
	cbreak();
	keypad(stdscr, 1);
	noecho();
}

int main(int argc, char **argv)
{
	char is_quit_game = FALSE;	/*stay in the game*/
	int cur_y = 0;
	int cur_x = 0;
	int row, col;
	int c;
	enum speed spd = one;
	enum key_value key;
	cell *cell_zero = NULL;	/*main list*/
	cell *cell_next = NULL;	/*temporary list*/
	cell *cell_src = NULL;	/*to save the source list*/
	start_curses_mode();
	getmaxyx(stdscr, row, col);
	if(!has_colors()) {
		show_msg(row, col, _("Your terminal don't support colors\n"));
	}
	else {
		show_msg(row, col, _("Your terminal support colors\n"));
		start_color();
	}
	while(!is_quit_game) {
		c = getch();
		key = check_key(c);
		switch(key) {
		case mv:
			move_carriage(row, col, c, &cur_y, &cur_x);
			break;
		case add:
			if(FALSE == is_in_list(cell_zero, cur_y, cur_x)) {
				add_cell(&cell_zero, cur_y, cur_x, alive);
				show_cell(cur_y, cur_x);
			}
			else {
				rm_cell(&cell_zero, cur_y, cur_x);
				hide_cell(cur_y, cur_x);
			}
			break;
		case finish:
			if(cell_zero == NULL) {
				show_msg(row, col, _("Initial conditions aren't set"));
				move(cur_y, cur_x);
			}
			else {
				automatic_rendering(cell_zero, spd, row, col);
				cur_y = 0;
				cur_x = 0;
			}
			break;
		case esc:
			is_quit_game = TRUE;
		case clrscr:
			clear_list(&cell_zero);
			clear();
			cur_y = 0;
			cur_x = 0;
			move(0, 0);
			break;
		case src:
			break;
		default:
			break;
		}
	}
	endwin();
	return 0;
}
