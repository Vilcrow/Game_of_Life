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
#include "carriage.h"

void move_carriage(const int row, const int col, int c, int *cur_y, int *cur_x)
{
	switch(c) {
	case (KEY_UP):
		*cur_y += -1;
		break;
	case (key_up):
		*cur_y += -1;
		break;
	case (KEY_DOWN):
		*cur_y += 1;
		break;
	case (key_down):
		*cur_y += 1;
		break;
	case (KEY_LEFT):
		*cur_x += -1;
		break;
	case (key_left):
		*cur_x += -1;
		break;
	case (KEY_RIGHT):
		*cur_x += 1;
		break;
	case (key_right):
		*cur_x += 1;
		break;
	}
	if(*cur_y < 0)
		*cur_y = row-1-msgboxheight;
	else if(*cur_y > row-1-msgboxheight)
		*cur_y = 0;
	if(*cur_x < 0)
		*cur_x = col-1;
	else if(*cur_x > col-1)
		*cur_x = 0;
	move(*cur_y, *cur_x);
}

enum key_value check_key(const int c)
{
	if(c == KEY_UP || c == key_up || c == KEY_DOWN || c == key_down ||
	   c == KEY_LEFT || c == key_left || c == KEY_RIGHT || c == key_right)
		return mv;
	else if(c == key_enter)
		return add;
	else if(c == key_finish)
		return finish;
	else if(c == key_escape)
		return esc;
	else if(c == key_clear)
		return clrscr;
	else if(c == key_source)
		return src;
	return -1;
}
