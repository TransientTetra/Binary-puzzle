#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "conio2.h"
#include "draw.h"
#include "memory.h"


//func makes a mallocated table of size n of field structs, returns ptr to it
struct field ** make_table(int n)
{
	struct field ** table;
	table = (struct field **) malloc(n * sizeof(struct field *));
	int i;

	for (i = 0; i < n; ++i)
	{
		table[i] = (struct field *) malloc(n * sizeof(struct field));
	}

	for (i = 0; i < n; ++i)
	{
		int j;
		for (j = 0; j < n; ++j)
		{
			table[i][j].filled = 0;
			table[i][j].value = ' ';
			table[i][j].initialized = 0;
			table[i][j].possibleone = 1;
			table[i][j].possiblezero = 1;
			table[i][j].reason_zero = 0;
			table[i][j].reason_one = 0;
		}
	}

	return table;
}

//frees up mallocated previously table
void del_table(struct field ** table, int size)
{
	int i;
	for (i = 0; i < size; ++i)
	{
		free(table[i]);
	}
	free(table);
}

//func initializes the table from the init file which contains
//the given initial config of table
void init_table(struct field ** board, int size)
{
	FILE *init;
	init = fopen("init.txt", "r");

	int i;
	for (i = 0; i < size; ++i)
	{
		int j;
		for (j = 0; j < size; ++j)
		{
			char temp = fgetc(init);
			if (temp == '1' || temp == '0')
			{
				board[i][j].value = temp;
				board[i][j].filled = 1;
				board[i][j].initialized = 1;
				board[i][j].possiblezero = 0;
				board[i][j].possibleone = 0;
				board[i][j].reason_zero = 4;
				board[i][j].reason_one = 4;
			}
			else
			{
				board[i][j].filled = 0;
			}
		}
	}
	fclose(init);
}


//func fills the board with random number of randomly chosen ones and
//zeroes which fulfill the rules
void partial_random_fill(struct field **board, int size)
{
	srand((unsigned int)time(NULL));
	int amount_fields = 0;
	amount_fields = rand() % (size * size);

	int i;
	for (i = 0; i < amount_fields; ++i)
	{
		int randx = rand() % size;
		int randy = rand() % size;

		if (board[randx][randy].initialized != 1 && board[randx][randy].filled == 0)
		{
			int temp_rand_value = rand() % 2;
			if (temp_rand_value == 0)
			{
				if (board[randx][randy].possiblezero == 1)
				{
					board[randx][randy].value = '0';
					board[randx][randy].filled = 1;
					board[randx][randy].initialized = 1;
				}
			}
			else if (temp_rand_value == 1)
			{
				if (board[randx][randy].possibleone == 1)
				{
					board[randx][randy].value = '1';
					board[randx][randy].filled = 1;
					board[randx][randy].initialized = 1;
				}
			}
		}
		check_rules(board, size);
	}
}

//this func asks for size between
//min board size and what screen allows and creates new board
//randomly filled, returns pointer to it
struct field ** resize_board(int *size, int *x, int *y)
{
	int tempsize = 0;
	struct text_info current_screen;
	gettextinfo(&current_screen);
	int screen_width = current_screen.screenwidth;
	int screen_height = current_screen.screenheight;
	do
	{
		clrscr();
		draw_horizontal_line(3, 3, 50);
		draw_horizontal_line(3, 14, 50);
		draw_vertical_line(3, 3, 12);
		draw_vertical_line(52, 3, 12);
		gotoxy(22, 4);
		cputs("Nowa plansza");
		gotoxy(5, 6);
		cputs("Wprowadz rozmiar tworzonej planszy.");
		gotoxy(5, 7);
		cputs("(Dwie cyfry, np. 02, 14)");
		gotoxy(5, 8);
		cputs("Wprowadzony rozmiar musi byc parzysty, wiekszy");
		gotoxy(5, 9);
		cputs("niz 1 i odpowiedni do rozmiaru okna.");
		gotoxy(22, 10);

		char input[2] = {'/0', '/0'};
		input[0] = getch();
		putchar(input[0]);
		input[1] = getch();
		putchar(input[1]);
		getch();

		tempsize = (10 * ((int)input[0] - 48)) + ((int)input[1] - 48);

		if (tempsize < 2 || tempsize > screen_height - POPUP_HEIGHT || tempsize > screen_width - INSTRUCTION_WIDTH || tempsize % 2 != 0)
		{
			clrscr();
			draw_horizontal_line(3, 3, 50);
			draw_horizontal_line(3, 14, 50);
			draw_vertical_line(3, 3, 12);
			draw_vertical_line(52, 3, 12);
			gotoxy(22, 4);
			cputs("Blad!");
			gotoxy(5, 6);
			cputs("Wprowadzony rozmiar jest nieprawidlowy.");
			gotoxy(5, 7);
			cputs("Wprowadzony rozmiar musi byc parzysty, wiekszy");
			gotoxy(5, 8);
			cputs("niz 1 i odpowiedni do rozmiaru okna.");
			gotoxy(10, 10);
			cputs("Wcisnij dowolny klawisz...");
			getch();
		}

	}while (tempsize < 2 || tempsize > screen_height - POPUP_HEIGHT || tempsize > screen_width - INSTRUCTION_WIDTH || tempsize % 2 != 0);

	*size = tempsize;
	struct field **interboard;
	interboard = make_table(tempsize);

	char filename[32];
	sprintf(filename, "board%d.txt", tempsize);

	FILE *save;
	save = fopen(filename, "r");
	if (save == NULL)
	{
		save = fopen(filename, "ab+");

		struct field **tempboard;
		tempboard = make_table(tempsize);
		partial_random_fill(tempboard, tempsize);
		int i;
		for (i = 0; i < tempsize; ++i)
		{
			int j;
			for (j = 0; j < tempsize; ++j)
			{
				fputc(tempboard[i][j].value, save);
			}
		}
		
	}
	fclose(save);
	save = fopen(filename, "r");

	int i;
	for (i = 0; i < tempsize; ++i)
	{
		int j;
		for (j = 0; j < tempsize; ++j)
		{
			char temp = fgetc(save);
			if (temp == '1' || temp == '0')
			{
				interboard[i][j].value = temp;
				interboard[i][j].filled = 1;
				interboard[i][j].initialized = 1;
				interboard[i][j].possiblezero = 0;
				interboard[i][j].possibleone = 0;
				interboard[i][j].reason_zero = 4;
				interboard[i][j].reason_one = 4;
			}
			else
			{
				interboard[i][j].filled = 0;
			}
		}
	}

	fclose(save);
	*x = 0;
	*y = 0;
	gotoxy(BOARDX + 1, BOARDY + 1);
	return interboard;
}
