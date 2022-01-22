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
#include "const.h"
#include "msgbox.h"

void show_msg(const int row, const int col, const char *message)
{
	clear_msg_line(row, col);
	move(row-1, 0);
	attrset(COLOR_PAIR(cp_gb));
	addstr(message);
	attroff(COLOR_PAIR(cp_gb));
	move(0, 0);
}

void clear_msg_line(const int row, const int col)
{
	int j;
	for(j = 0; j < col; ++j)
		mvaddch(row-1, j, ' ');
}

void show_settings(const char mode, const enum speed spd, const int row,
					const int cur_y, const int cur_x)
{
	attrset(COLOR_PAIR(cp_rb));
	mvprintw(row-msgboxheight, 0, "Mode: %c | Speed: %d ", mode, spd);
	attroff(COLOR_PAIR(cp_rb));
	move(cur_y, cur_x);
}

char change_mode(char mode)
{
	if(mode == ed_mode)
		return sim_mode;
	else
		return ed_mode;
}
