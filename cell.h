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

#ifndef CELL_H_SENTRY
#define CELL_H_SENTRY

void add_cell(cell **first, const int y, const int x, const unsigned int gen,
															enum status st);
void rm_cell(cell **first, const int y, const int x);
void show_cell(const int y, const int x);
void hide_cell(const int y, const int x);
char is_in_list(cell *first, const int y, const int x);
char is_visible(const int row, const int col, const int y, const int x);
char will_added(cell *first, const int row, const int col,
				const int y, const int x);
void show_cells(cell *first, const int row, const int col);
void copy_list(cell **to, cell *from);
void move_all_cells(const int row, const int col, const char c, cell **current);
void move_to_first_cell(cell *first, int *cur_y, int *cur_x);

#endif
