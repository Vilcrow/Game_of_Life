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
#include "colpairs.h"
#include "msgbox.h"
#include "preparation.h"
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
	int cur_y = 0;
	int cur_x = 0;
	int row, col;
	int c;
	char mode = ed_mode;
	enum speed spd = spd_zero;
	enum key_value key;
	char path[pathmaxlen];
	cell *cell_zero = NULL;
	cell *cell_current = NULL;
	start_curses_mode();
	getmaxyx(stdscr, row, col);
	if(argc > 1)
		check_command_line_arg(argc, argv, &cell_current, row, col);
	if(!has_colors()) {
		show_msg(row, col, _("Your terminal don't support colors"));
	}
	else {
		start_color();
		set_color_pairs();
	}
	show_msg(row, col, _("ENTER - add/remove a cell | 'r' - run the simulation"));
	show_settings(mode, spd, row, cur_y, cur_x);
	while((c = getch()) != key_escape) {
		key = check_key(c);
		switch(key) {
		case mv:
			move_carriage(row, col, c, &cur_y, &cur_x);
			break;
		case add:
			if(FALSE == is_in_list(cell_current, cur_y, cur_x)) {
				add_cell(&cell_current, cur_y, cur_x, 0, alive);
				show_cell(cur_y, cur_x);
			}
			else {
				rm_cell(&cell_current, cur_y, cur_x);
				hide_cell(cur_y, cur_x);
			}
			break;
		case run:
			if(cell_current == NULL) {
				show_msg(row, col, _("Initial conditions aren't set"));
				move(cur_y, cur_x);
			}
			else {
				show_msg(row, col, _("Simulation | 'SPACE' - stop the simulation"));
				mode = change_mode(mode);
				show_settings(mode, spd, row, cur_y, cur_x);
				render_result(&cell_current, spd, row, col);
				mode = change_mode(mode);
				cur_y = 0;
				cur_x = 0;
				show_msg(row, col, _("ENTER - add/remove a cell | 'r' - run the simulation"));
				show_settings(mode, spd, row, cur_y, cur_x);
				move(0, 0);
			}
			break;
		case clrscr:
			clear_list(&cell_current);
			clear_field(row, col);
			cur_y = 0;
			cur_x = 0;
			move(0, 0);
			break;
		case mkzc:	/*make the cell_zero current*/
			copy_list(&cell_current, cell_zero);
			show_cells(cell_current, row, col);
			cur_y = 0;
			cur_x = 0;
			move(0, 0);
			break;
		case svcl:	/*save current list to cell_zero*/
			copy_list(&cell_zero, cell_current);
			break;
		case speed:
			++spd;
			if(spd > spd_max)
				spd = spd_zero;
			show_settings(mode, spd, row, cur_y, cur_x);
			break;
		case write:
			write_to_file(cell_current, row, col);
			break;
		case read:
			get_path(path, row, col);
			read_from_file(&cell_current, path, row, col);
			show_cells(cell_current, row, col);
			break;
		default:
			break;
		}
	}
	endwin();
	return 0;
}
