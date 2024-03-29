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
#include <stdlib.h>
#include "const.h"
#include "cell.h"
#include "colpairs.h"
#include "preparation.h"
#include "renderer.h"

void add_cell(cell **first, const int y, const int x, const unsigned int gen,
															enum status st)
{
	cell *tmp = NULL;
	cell *aux = *first;
	tmp = malloc(sizeof(cell));
	tmp->y = y;
	tmp->x = x;
	tmp->gen = gen;
	tmp->st = st;
	tmp->prev = NULL;
	tmp->next = NULL;
	if(*first == NULL)
		*first = tmp;
	else {
		while(aux != NULL) {
			if(tmp->y > aux->y) {
				aux = aux->next;
			}
			else if(tmp->y == aux->y) {
				if(tmp->x > aux->x)
					aux = aux->next;
				else if(tmp->x < aux->x) {
					if(aux != *first) {
						tmp->prev = aux->prev;
						aux->prev->next = tmp;
					}
					else
						*first = tmp;
					aux->prev = tmp;
					tmp->next = aux;
					break;
				}
			}
			else {
				if(aux == *first) {
					*first = tmp;
					tmp->next = aux;
					aux->prev = tmp;
					break;
				}
				else {
					aux->prev->next = tmp;
					tmp->prev = aux->prev;
					tmp->next = aux;
					aux->prev = tmp;	
					break;
				}
			}
		}
		if(aux == NULL) {
			aux = *first;
			while(aux->next != NULL) {
				aux = aux->next;
			}
			aux->next = tmp;
			tmp->prev = aux;
		}
	}
}

void rm_cell(cell **first, const int y, const int x)
{
	cell *tmp = *first;
	while(tmp->y != y) {
		tmp = tmp->next;
	}
	while(tmp->x != x) {
		tmp = tmp->next;
	}
	if(tmp == *first) {
		if(tmp->next != NULL) {
			*first = tmp->next;	
			tmp->next->prev = NULL;
			free(tmp);
		}
		else {
			*first = NULL;
			free(tmp);
		}
	}
	else if(tmp->next == NULL) {
		tmp->prev->next = NULL;
		free(tmp);
	}
	else {
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		free(tmp);
	}
}

void hide_cell(const int y, const int x)
{
	mvaddch(y, x, empty_char);
	move(y, x);
}

void show_cell(const int y, const int x)
{
	mvaddch(y, x, cell_char);
	move(y, x);
}

char is_in_list(cell *first, const int y, const int x)
{
	cell *tmp = first;
	while(tmp != NULL) {
		if(tmp->y == y && tmp->x == x)
			return TRUE;
		else
			tmp = tmp->next;
	}
	return FALSE;
}

char is_visible(const int row, const int col, const int y, const int x)
{
	if(y < 0 || y > row-1-msgboxheight || x < 0 || x > col-1)
		return FALSE;
	else
		return TRUE;
}

char will_added(cell *first, const int row, const int col,
				const int y, const int x)
{
	if((TRUE == is_visible(row, col, y, x)) && (FALSE == is_in_list(first, y, x)))
		return TRUE;
	else
		return FALSE;
}

void show_cells(cell *first, const int row, const int col)
{
	cell *tmp = first;
	clear_field(row, col);
	enum color_pairs cp;
	while(tmp != NULL) {
		cp = get_color_pair(tmp->gen);
		attrset(COLOR_PAIR(cp));
		if(is_visible(row, col, tmp->y, tmp->x))
			mvaddch(tmp->y, tmp->x, cell_char);
		attroff(COLOR_PAIR(cp));
		tmp = tmp->next;
	}
	refresh();
	move(0, 0);
}

void copy_list(cell **to, cell *from)
{
	if(*to != NULL)	/*list is not empty*/
		clear_list(to);
	cell *tmp = from;
	while(tmp != NULL) {
		add_cell(to, tmp->y, tmp->x, tmp->gen, tmp->st);
		tmp = tmp->next;
	}	
}

void move_all_cells(const int row, const int col, const char c, cell **current)
{
	cell *tmp = *current;
	int dy, dx;
	switch(c) {
	case key_up_b:
		dy = -1;
		dx = 0;
		break;
	case key_down_b:
		dy = 1;
		dx = 0;
		break;
	case key_left_b:
		dy = 0;
		dx = -1;
		break;
	case key_right_b:
		dy = 0;
		dx = 1;
		break;
	}
	while(tmp != NULL) {
		tmp->y += dy;
		tmp->x += dx;
		tmp = tmp->next;
	}
}

void move_to_first_cell(cell *first, int *cur_y, int *cur_x)
{
	if(first != NULL) {
		*cur_y = first->y;
		*cur_x = first->x;
		move(*cur_y, *cur_x);
	}
}
