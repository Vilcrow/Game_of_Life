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
#include "const.h"
#include "renderer.h"
#include "cell.h"
#include "preparation.h"
#include "msgbox.h"

void render_result(cell **first, enum speed spd, const int row, const int col)
{
	curs_set(0);
	if(spd != 0) {
		show_msg(row, col, _("Simulation. SPACE - stop"));
		timeout(timeout_min/spd);	/*set rendering speed*/
		automatic_rendering(first, row, col);
		clear_msg_line(row, col);
	}
	else
		render_one_step(first, row, col);
	curs_set(1);
}

char are_lists_same(cell *src, cell *cmp)
{
	cell *tsrc = src;
	cell *tcmp = cmp;
	while(tsrc != NULL && tcmp != NULL) {
		if((tsrc->y == tcmp->y) && (tsrc->x == tcmp->x)) {
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

void automatic_rendering(cell **first, const int row, const int col)
{
	cell *tmp = NULL;
	int c;
	while((c = getch()) != key_pause) {
		if(are_lists_same(*first, tmp) == TRUE || *first == NULL)
			break;
		switch(c) {
		case ERR:
			copy_list(&tmp, *first);
			render_one_step(first, row, col);
			break;
		}
	}	
}

void render_one_step(cell **first, const int row, const int col)
{
	cell *next = NULL;
	copy_list(&next, *first);
	preparate_env(&next, first, row, col);
	create_new_generation(&next, first, row, col);
	show_cells(*first, row, col);	
}

void clear_field(const int row, const int col)
{
	int i, j;
	for(i = 0; i < row-msgboxheight; ++i)
		for(j = 0; j < col; ++j)
			mvaddch(i, j, empty_char);
}

void write_to_file(cell *first, const int row, const int col)
{
	FILE *to;
	int i, j;
	char path[pathmaxlen];
	get_path(path, row, col);
	if(path[0] != '\0') {
		to = fopen(path, "w");
		if(!to) {
			show_msg(row, col, _("Failed to write"));
		}
		else {
			for(i = 0; i < row-msgboxheight; ++i) {
				for(j = 0; j < col; ++j) {
					if(TRUE == is_in_list(first, i, j))
						fputc(cell_char, to);
					else
						fputc(empty_char, to);
				}
				fputc('\n', to);
			}	
			fclose(to);
			show_msg(row, col, _("Done"));
		}
	}
	else
		show_msg(row, col, _("Failed to write"));
}

void read_from_file(cell **first, const char *path, const int row,
													const int col)
{
	FILE *from;
	int i, j, c;
	char line_end;
	if(path[0] != '\0') {
		from = fopen(path, "r");
		if(!from) {
			show_msg(row, col, _("Failed to read"));
		}
		else {
			clear_list(first);
			for(i = 0; i < row-msgboxheight; ++i) {
				for(j = 0; j <= col; ++j) {
					line_end = FALSE;
					c = fgetc(from);
					if(c == '\n') {
						line_end = TRUE;
						break;
					}
					else if(c == EOF)
						break;	
					else if(c != empty_char) {
						add_cell(first, i, j, 0, alive);
					}
				}
				if(c == EOF)
					break;
				if(!line_end) {	/*line from the file more window width*/
					while((c = fgetc(from)) != '\n') {
						;
					}
				}
			}
			fclose(from);
			show_msg(row, col, _("Done"));
		}
	}
	else
		show_msg(row, col, _("Canceled"));
}

void get_path(char *path, const int row, const int col) /*need fix*/
{
	int c;
	int i = 0;
	clear_msg_line(row, col);
	move(row-1, 0);
	echo();
	while((c = getch()) != key_enter) {
		if(c == key_escape) {
			noecho();
			path[0] = '\0';
			break;
		}
		else if(c == KEY_BACKSPACE) {
			mvaddch(row-1, i-1, empty_char);
			move(row-1, i-1);
			--i;
			if(i < 0) {
				i = 0;
			}
		}
		else if((c >= 32 && c <= 126) && (i < pathmaxlen-1)) {
			path[i] = c;
			++i;	
		}
	}
	noecho();
	path[i] = '\0';
}
