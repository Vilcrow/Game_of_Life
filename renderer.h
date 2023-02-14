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

#ifndef RENDERER_H_SENTRY
#define RENDERER_H_SENTRY

void render_result(cell **first, enum speed spd, const int row, const int col);
char are_lists_same(cell *src, cell *cmp);
void automatic_rendering(cell **first, const int row, const int col);
void render_one_step(cell **first, const int row, const int col);
void clear_field(const int row, const int col);
void write_to_file(cell *first, const int row, const int col);
void read_from_file(cell **first, const char *path, const int row,
													const int col);
void get_path(char *path, const int row, const int col);

#endif
