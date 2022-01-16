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

#include <stdlib.h>
#include "const.h"
#include "preparation.h"
#include "cell.h"

void preparate_env(cell **next, cell **first, const int row, const int col)
{
	cell *tmp = *first;
	while(tmp != NULL) {
		add_env(next, *first, tmp, row, col);
		tmp = tmp->next;
	}
	tmp = *first;
	*first = *next;
	clear_list(&tmp);
	*next = NULL; 
}

void add_env(cell **next, cell *first, cell *tmp, const int row, const int col)
{
	int cur_y, cur_x;
	int dy = -1;
	int dx = -1;
	int i, j;
	for(i = 0; i < 3; ++i) {
		cur_y = tmp->y + dy;
		for(j = 0; j < 3; ++j) {
			cur_x = tmp->x +dx;
			if(will_added(first, row, col, cur_y, cur_x))
				if(FALSE == is_in_list(*next, cur_y, cur_x))
					add_cell(next, cur_y, cur_x, dead);
			++dx;
		}
		dx = -1;
		++dy;
	}
}

enum status is_viable(cell *first, cell *tmp, const int row, const int col)
{
	int cur_y, cur_x;
	int dy = -1;
	int dx = -1;
	int i, j;
	char neighbors = 0;
	for(i = 0; i < 3; ++i) {
		cur_y = tmp->y + dy;
		for(j = 0; j < 3; ++j) {
			if(dy == 0 && dx == 0) {	/*cell itself*/
				++dx;
				continue;
			}
			cur_x = tmp->x + dx;	
			if(TRUE == is_visible(row, col, cur_y, cur_x)) {
				if(is_in_list(first, cur_y, cur_x))
					if(alive == get_status(first, cur_y, cur_x))
						++neighbors;
			}
			++dx;
		}
		dx = -1;
		++dy;
	}
	if(tmp->st == dead) {
		if(neighbors == 3)
			return alive;
	}	
	else {
		if(neighbors == 2 || neighbors == 3)
			return alive;
	}
	return dead;
}

enum status get_status(cell *first, const int y, const int x)
{
	cell *tmp = first;
	while(tmp != NULL) {
		if(tmp->y == y && tmp->x == x)
			return tmp->st;
		tmp = tmp->next;
	}
	return -1;
}

void create_new_generation(cell **next, cell **first, const int row, const int col)
{
	cell *tmp = *first;
	while(tmp != NULL) {
		if(alive == is_viable(*first, tmp, row, col)) {
			add_cell(next, tmp->y, tmp->x, alive);
		}
		tmp = tmp->next;
	}
	tmp = *first;
	*first = *next;
	*next = NULL;
	clear_list(&tmp);
}

void clear_list(cell **first)
{
	cell *tmp = *first;
	while(tmp != NULL) {
		*first = tmp->next;
		free(tmp);
		tmp = *first;
	}
}
