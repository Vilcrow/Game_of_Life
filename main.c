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
#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "carriage.h"
#include "cell.h"
#include "colpairs.h"
#include "msgbox.h"
#include "preparation.h"
#include "renderer.h"
#include "interface.h"

void start_curses_mode()
{
	initscr();
	cbreak();
	keypad(stdscr, 1);
	noecho();
}

int main()
{
	int row, col;
	start_curses_mode();
	getmaxyx(stdscr, row, col);
	if(!has_colors()) {
		show_msg(row, col, _("Your terminal don't support colors"));
	}
	else {
		start_color();
		set_color_pairs();
	}
	input_processing();
	endwin();
	return 0;
}
