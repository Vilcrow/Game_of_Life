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

#ifndef CONST_H_SENTRY
#define CONST_H_SENTRY

#define _(STR) (STR)
#define N_(STR) (STR)	/*don't translate*/

#define TRUE 1
#define FALSE 0

enum {cell_char = '#'};

enum {key_up = 'k'};
enum {key_down = 'j'};
enum {key_left = 'h'};
enum {key_right = 'l'};
enum {key_enter = 10};
enum {key_escape = 27};
enum {key_finish = 'f'};
enum status {dead, alive};
enum key_value {mv, add, finish, esc};

typedef struct one_cell {
	int y;
	int x;
	enum status st;
	struct one_cell *prev;
	struct one_cell *next;
} cell;


#endif
