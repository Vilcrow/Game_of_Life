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

#ifndef PREPARATION_H_SENTRY
#define PREPARATION_H_SENTRY

void preparate_env(cell **next, cell **first, const int row, const int col);
void add_env(cell **next, cell *first, cell *tmp, const int row, const int col);
enum status is_viable(cell *first, cell *tmp, const int row, const int col);
enum status get_status(cell *first, const int y, const int x);
void create_new_generation(cell **next, cell **first,
							const int row, const int col);
void clear_list(cell **first);
void update_generation_num(cell *first);
void check_command_line_arg(const int argc, char **argv, cell **current,
							const int row, const int col);
void show_help_page();
char argv_type(const char *string);
char string_comparison(const char *pattern, const char *string);

#endif
