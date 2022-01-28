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

#ifndef INTERFACE_H_SENTRY
#define INTERFACE_H_SENTRY


void input_processing();
void zeroize_curyx(int *cur_y, int *cur_x);
void case_add(cell **current, const int cur_y, const int cur_x);
void case_run(cell **current, const enum speed spd);
void case_make_zero_current(cell **current, cell *zero,
							const int row, const int col);
void case_clear_screen(cell **current, const int row, const int col);

#endif
