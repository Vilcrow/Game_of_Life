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
#include "colpairs.h"

void set_color_pairs()
{
	init_pair(cp_wb, COLOR_WHITE, COLOR_BLACK);
	init_pair(cp_yb, COLOR_YELLOW, COLOR_BLACK);
	init_pair(cp_gb, COLOR_GREEN, COLOR_BLACK);
	init_pair(cp_cb, COLOR_CYAN, COLOR_BLACK);
	init_pair(cp_bb, COLOR_BLUE, COLOR_BLACK);
	init_pair(cp_mb, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(cp_rb, COLOR_RED, COLOR_BLACK);
}

enum color_pairs get_color_pair(const unsigned int gen)
{
	if(gen > cp_rb)
		return cp_rb;
	else
		return gen;
}
