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

void automatic_rendering(cell *first, enum speed spd, const int row,
														const int col)
{
	cell *tmp = NULL;
	cell *next = NULL;
	cell *start = NULL;
	int key;
	timeout(timeout_min/spd);
	curs_set(0);
	copy_list(&tmp, first);
	while((key = getch()) != key_escape) {
		if(are_lists_same(start, tmp) == TRUE || tmp == NULL)
			break;
		switch(key) {
		case key_pause:
			while((key = getch()) != key_pause) {
				;
			}
		case ERR:
			copy_list(&start, tmp);
			copy_list(&next, tmp);
			preparate_env(&next, &tmp, row, col);
			create_new_generation(&next, &tmp, row, col);
			show_cells(tmp);	
			break;
		}
	}	
	curs_set(1);
}

char are_lists_same(cell *src, cell *cmp)
{
	cell *tsrc = src;
	cell *tcmp = cmp;
	while(tsrc != NULL && tcmp != NULL) {
		if((tsrc->y == tcmp->y) && (tsrc->x == tcmp->x) && (tsrc->st == tcmp->st)) {
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
