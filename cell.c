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
#include <ncurses.h>
#include "const.h"
#include "cell.h"

void add_alive_cell(cell **first, int y, int x)
{
	cell *tmp = NULL;
	cell *aux = *first;
	tmp = malloc(sizeof(cell));
	tmp->y = y;
	tmp->x = x;
	tmp->st = alive;
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
					aux->prev = tmp;
					tmp->next = aux;
					aux->prev->next = tmp;
					tmp->prev = aux->prev;
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
	mvaddch(y, x, ' ');
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