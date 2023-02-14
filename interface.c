/*
Game of Life

Copyright (C) 2022-2023 S.V.I 'Vilcrow', <svi@vilcrow.net>
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
#include "const.h"
#include "interface.h"
#include "carriage.h"
#include "cell.h"
#include "msgbox.h"
#include "preparation.h"
#include "renderer.h"

void input_processing()
{
	int cur_y = 0;
	int cur_x = 0;
	int row, col;
	int c;
	enum key_value key;
	enum speed spd = spd_zero;
	char path[pathmaxlen];
	cell *cell_zero = NULL;
	cell *cell_current = NULL;
	getmaxyx(stdscr, row, col);
	show_settings(spd, row);
	zeroize_curyx(&cur_y, &cur_x);
	move(0, 0);
	while((c = getch()) != key_escape) {
		show_msg(row, col, _("'m' - get help. ESC - quit the game"));
		move(cur_y, cur_x);
		key = check_key(c);
		switch(key) {
		case mv:
			move_carriage(row, col, c, &cur_y, &cur_x);
			break;
		case bmv:
			move_all_cells(row, col, c, &cell_current);
			show_cells(cell_current, row, col);
			zeroize_curyx(&cur_y, &cur_x);
			break;
		case add:
			case_add(&cell_current, cur_y, cur_x);
			break;
		case run:
			case_run(&cell_current, spd);
			zeroize_curyx(&cur_y, &cur_x);
			break;
		case clrscr:
			case_clear_screen(&cell_current, row, col);
			zeroize_curyx(&cur_y, &cur_x);
			move(cur_y, cur_x);
			break;
		case mkzc:	/*make the cell_zero current*/
			case_make_zero_current(&cell_current, cell_zero, row, col);
			zeroize_curyx(&cur_y, &cur_x);
			move(cur_y, cur_x);
			break;
		case svcl:	/*save current list to cell_zero*/
			copy_list(&cell_zero, cell_current);
			break;
		case speed:
			++spd;
			if(spd > spd_max)
				spd = spd_zero;
			show_settings(spd, row);
			move(cur_y, cur_x);
			break;
		case write:
			write_to_file(cell_current, row, col);
			break;
		case read:
			get_path(path, row, col);
			read_from_file(&cell_current, path, row, col);
			show_cells(cell_current, row, col);
			break;
		case pattern:
			break;
		case pattlist:
			break;
		case manual:
			show_manual(row, col);
			show_cells(cell_current, row, col);
			break;
		case mvtofirst:
			move_to_first_cell(cell_current, &cur_y, &cur_x);
			break;
		default:
			break;
		}
	}
}

void zeroize_curyx(int *cur_y, int *cur_x)
{
	*cur_y = 0;
	*cur_x = 0;
}

void case_add(cell **current, const int cur_y, const int cur_x)
{
	if(!is_in_list(*current, cur_y, cur_x)) {
		add_cell(current, cur_y, cur_x, 0, alive);
		show_cell(cur_y, cur_x);
	}
	else {
		rm_cell(current, cur_y, cur_x);
		hide_cell(cur_y, cur_x);
	}
}

void case_run(cell **current, const enum speed spd)
{
	int row, col;
	getmaxyx(stdscr, row, col);
	clear_msg_line(row, col);
	render_result(current, spd, row, col);
}

void case_make_zero_current(cell **current, cell *zero,
							const int row, const int col)
{
	copy_list(current, zero);
	show_cells(*current, row, col);
	show_msg(row, col, _("Done"));
}

void case_clear_screen(cell **current, const int row, const int col)
{
	clear_list(current);
	clear_field(row, col);
	show_msg(row, col, _("Clean"));
}
