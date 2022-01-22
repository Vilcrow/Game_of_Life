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
#include "renderer.h"
#include "cell.h"
#include "preparation.h"

void render_result(cell **first, enum speed spd, const int row, const int col)
{
	curs_set(0);
	if(spd != 0) {
		timeout(timeout_min/spd);	/*set rendering speed*/
		automatic_rendering(first, row, col);
	}
	else
		render_one_step(first, row, col);
	curs_set(1);
}

char are_lists_same(cell *src, cell *cmp)
{
	cell *tsrc = src;
	cell *tcmp = cmp;
	while(tsrc != NULL && tcmp != NULL) {
		if((tsrc->y == tcmp->y) && (tsrc->x == tcmp->x)) {
			tsrc = tsrc->next;
			tcmp = tcmp->next;
		}
		else
			return FALSE;
	}
	if(tsrc == NULL && tcmp == NULL)
		return TRUE;
	return FALSE;
}

void automatic_rendering(cell **first, const int row, const int col)
{
	cell *tmp = NULL;
	int c;
	while((c = getch()) != key_pause) {
		if(are_lists_same(*first, tmp) == TRUE || *first == NULL)
			break;
		switch(c) {
		case ERR:
			copy_list(&tmp, *first);
			render_one_step(first, row, col);
			break;
		}
	}	
}

void render_one_step(cell **first, const int row, const int col)
{
	cell *next = NULL;
	copy_list(&next, *first);
	preparate_env(&next, first, row, col);
	create_new_generation(&next, first, row, col);
	show_cells(*first, row, col);	
}

void clear_field(const int row, const int col)
{
	int i, j;
	for(i = 0; i < row-msgboxheight; ++i)
		for(j = 0; j < col; ++j)
			mvaddch(i, j, ' ');
}
