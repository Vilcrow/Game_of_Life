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
#include <stdio.h>
#include "const.h"
#include "preparation.h"
#include "cell.h"
#include "renderer.h"

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
					add_cell(next, cur_y, cur_x, 0, dead);
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
			add_cell(next, tmp->y, tmp->x, tmp->gen, alive);
		}
		tmp = tmp->next;
	}
	tmp = *first;
	*first = *next;
	*next = NULL;
	clear_list(&tmp);
	update_generation_num(*first);
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

void update_generation_num(cell *first)
{
	cell *tmp = first;
	while(tmp != NULL) {
		++tmp->gen;
		tmp = tmp->next;
	}
}

void check_command_line_arg(const int argc, char **argv, cell **current,
							const int row, const int col)
{
	int type;
	if(argc > 3) {
		printf(_("Too many arguments.\n"));
		exit(1);
	}
	if(argc > 1) {
		type = argv_type(argv[1]);
		switch(type) {
		case -1:
			printf(_("Invalid option '%s'. Try 'gameoflife -h' for more information.\n"), argv[1]);
			exit(2);
			break;
		case help:
			show_help_page();
			exit(0);
			break;
		case file:
			read_from_file(current, argv[2], row, col);
			show_cells(*current, row, col);
			break;
		case man:
			break;
		case pattern:
			break;
		}
	}
}

void show_help_page()
{
	printf(_("Available commands:\n"));
	printf(_("-h\t\t\tDisplay help\n"));
	printf(_("-m\t\t\tOpen manual\n"));
	printf(_("-f [name]\t\tOpen the specified file\n"));
	printf(_("-p [name]\t\tOpen the specified pattern\n"));
}

char argv_type(const char *string)
{
	char shelp[] = "-h";
	char sman[] = "-m";
	char spattern[] = "-p";
	char sfile[] = "-f";
	if(TRUE == string_comparison(shelp, string))
		return help;
	else if(TRUE == string_comparison(sman, string))
		return man;
	else if(TRUE == string_comparison(spattern, string))
		return pattern;
	else if(TRUE == string_comparison(sfile, string))
		return file;
	else
		return -1;
}

char string_comparison(const char *pattern, const char *string)
{
	int i = 0;
	while(pattern[i] != '\0' && string[i] != '\0') {
		if(pattern[i] == string[i])
			++i;
		else
			return FALSE;
	}
	if((pattern[i] == '\0' && string[i] != '\0') ||
		(string[i] == '\0' && pattern[i] != '\0'))
		return FALSE;
	return TRUE;	/*strings are matched*/
}

