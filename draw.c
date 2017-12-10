#include <stdio.h>
#include "conio2.h"
#include "draw.h"

//func draws a horizontal line in point(x, y) that is n long
void draw_horizontal_line(int x, int y, int n)
{
	
	int i;
	for (i = 0; i < n; ++i)
	{
		gotoxy(x, y);
		putch('-');
		++x;
	}
}

//func draws a vertical line
void draw_vertical_line(int x, int y, int n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		gotoxy(x, y);
		putch('|');
		++y;
	}
}

//func draws instructions and completed points and author's name
void draw_instruction(int x, int y)
{
	int tempx = wherex();
	int tempy = wherey();

	//this section prints instructions
	gotoxy(INSTRUCTIONORIENT + 1, 2);
	cputs("strzalki - przemieszczanie sie kursorem po planszy");
	gotoxy(INSTRUCTIONORIENT + 1, 3);
	cputs("esc - wyjscie z programu");
	gotoxy(INSTRUCTIONORIENT + 1, 4);
	cputs("n - nowa gra");
	gotoxy(INSTRUCTIONORIENT + 1, 5);
	cputs("01 - wpisanie znaku na plansze");
	gotoxy(INSTRUCTIONORIENT + 1, 6);
	cputs("o - losowe czesciowe wypelnienie planszy");
	gotoxy(INSTRUCTIONORIENT + 1, 7);
	cputs("p - prosta podpowiedz");
	gotoxy(INSTRUCTIONORIENT + 1, 8);
	cputs("r - zmiana rozmiaru planszy");
	gotoxy(INSTRUCTIONORIENT + 1, 9);
	cputs("k - zazn. pol w ktore nie da sie wpisac 1 ani 0");
	gotoxy(INSTRUCTIONORIENT + 1, 10);
	cputs("d - wyswietlenie liczby zer i jedynek");
	
	//this section draws the frame	
	draw_horizontal_line(INSTRUCTIONORIENT, 1, 51);
	draw_horizontal_line(INSTRUCTIONORIENT, 17, 51);
	draw_horizontal_line(INSTRUCTIONORIENT, 24, 51);
	draw_vertical_line(INSTRUCTIONORIENT, 1, 24);
	draw_vertical_line(INSTRUCTIONORIENT + 51, 1, 24);
	
	//this section draws other
	char txt[32];
	gotoxy(INSTRUCTIONORIENT + 1, 18);
	cputs("Autor:");
	gotoxy(INSTRUCTIONORIENT + 1, 19);
	cputs("Mikolaj Sperkowski nr indeksu 171725");
	gotoxy(INSTRUCTIONORIENT + 1, 20);
	cputs("Zaimplementowano:");
	gotoxy(INSTRUCTIONORIENT + 1, 21);
	cputs("a, b, c, d, e, f, g, h, i, j, k");
	gotoxy(INSTRUCTIONORIENT + 1, 22);
	cputs("Aktualna pozycja kursora:");
	gotoxy(INSTRUCTIONORIENT + 1, 23);
	sprintf(txt, "(%d, %d)", x, y);
	cputs(txt);
	gotoxy(tempx, tempy);

}


//func draws board, last two arguments specify the leftmost corner
void draw_board(struct field ** board, int size_board, int startx, int starty)
{
	int tempx = wherex();
	int tempy = wherey();

	draw_horizontal_line(startx, starty, size_board + 1);
	draw_horizontal_line(startx, starty + size_board + 1, size_board + 1);
	draw_vertical_line(startx + size_board + 1, starty, size_board + 2);
	draw_vertical_line(startx, starty, size_board + 2);

	int i;
	for (i = 0; i < size_board; ++i)
	{
		gotoxy(startx + 1, starty + 1);
		int j;
		for (j = 0; j < size_board; ++j)
		{
			if (board[i][j].filled == 1)
			{
				if (board[i][j].initialized == 1)
				{
					textbackground(CYAN);
					putch(board[i][j].value);
					textbackground(BLUE);
				}
				else putch(board[i][j].value);
			}
			else
			{
				putch(' ');
			}
		}
		++starty;
	}
	gotoxy(tempx, tempy);
}

//movement funcs
void move_up(int *y)
{
	if (*y > 0)
	{
		--*y;
		gotoxy(wherex(), wherey() - 1);
	}
}

void move_down(int *y, int size_board)
{
	if (*y < size_board - 1)
	{
		++*y;
		gotoxy(wherex(), wherey() + 1);
	}
}

void move_left(int *x)
{
	if (*x > 0)
	{
		--*x;
		gotoxy(wherex() - 1, wherey());
	}
}

void move_right(int *x, int size_board)
{
	if (*x < size_board - 1)
	{
		++*x;
		gotoxy(wherex() + 1, wherey());
	}
}

//displays an easy hint in instruction region
void easy_hint(struct field **board, int x, int y)
{
	int tempx = wherex();
	int tempy = wherey();

	draw_vertical_line(INSTRUCTIONORIENT + 37, 18, 6);

	if (board[x][y].possiblezero == 0 || board[x][y].possibleone == 0)
	{
		draw_horizontal_line(INSTRUCTIONORIENT + 52, 1, 28);
		draw_horizontal_line(INSTRUCTIONORIENT + 52, 6, 28);
		draw_vertical_line(INSTRUCTIONORIENT + 79, 1, 6);
	}

	gotoxy(INSTRUCTIONORIENT + 38, 18);
	cputs("Dozwolone");
	gotoxy(INSTRUCTIONORIENT + 38, 19);
	cputs("Na danym polu");
	gotoxy(INSTRUCTIONORIENT + 42, 21);
	
	if (board[x][y].possiblezero == 0 && board[x][y].possibleone == 0)
	{
		cputs("Zaden");
	}	
	if (board[x][y].possiblezero == 1)
	{
		cputs("0");
	}
	if (board[x][y].possibleone == 1)
	{
		gotoxy(INSTRUCTIONORIENT + 42, 22);
		cputs("1");
	}
	
	if (board[x][y].possiblezero == 0)
	{
		gotoxy(INSTRUCTIONORIENT + 53, 2);
		cputs("Powod dla zera:");
		gotoxy(INSTRUCTIONORIENT + 54, 3);
		if (board[x][y].reason_zero == 1) cputs("zlamana zasada pierwsza");
		if (board[x][y].reason_zero == 2) cputs("zlamana zasada druga");
		if (board[x][y].reason_zero == 3) cputs("zlamana zasada trzecia");
		if (board[x][y].reason_zero > 3) cputs("pole preinicjalizowane");
	}
	if (board[x][y].possibleone == 0)
	{
		gotoxy(INSTRUCTIONORIENT + 53, 4);
		cputs("Powod dla jedynki:");
		gotoxy(INSTRUCTIONORIENT + 54, 5);
		if (board[x][y].reason_one == 1) cputs("zlamana zasada pierwsza");
		if (board[x][y].reason_one == 2) cputs("zlamana zasada druga");
		if (board[x][y].reason_one == 3) cputs("zlamana zasada trzecia");
		if (board[x][y].reason_one > 3) cputs("pole preinicjalizowane");
	}

	gotoxy(tempx, tempy);
}


//highlights these fields that neither one nor zero can be put in
void simple_check_win(struct field **board, int size)
{
	int tempx = wherex();
	int tempy = wherey();
	int i;
	for (i = 0; i < size; ++i)
	{
		int j;
		for (j = 0; j < size; ++j)
		{
			if (board[i][j].initialized != 1 && board[i][j].filled == 0)
			{
				if (board[i][j].possibleone == 0 && board[i][j].possiblezero == 0)
				{
					gotoxy(j + BOARDX + 1, i + BOARDY + 1);
					textbackground(YELLOW);
					putch(' ');
					textbackground(BLUE);
				}
			}
		}
	}
	gotoxy(tempx, tempy);
}

//this func displays the number of zeroes and ones in each row and column
//next to said row or column
void display_amount(struct field **board, int size)
{
	int tempx = wherex();
	int tempy = wherey();

	draw_horizontal_line(BOARDX + size + 2, BOARDY, 5);
	draw_vertical_line(BOARDX + size + 4, BOARDY - 1, size + 2);
	draw_horizontal_line(BOARDX + size + 2, BOARDY + size + 1, 5);
	draw_horizontal_line(BOARDX + 1, BOARDY + size + 3, size + 6);
	draw_vertical_line(BOARDX + size + 1, BOARDY + size + 2, 3);
	gotoxy(BOARDX + size + 2, BOARDY + size + 2);
	cputs("Zer");
	gotoxy(BOARDX + size + 2, BOARDY + size + 4);
	cputs("Jedynek");
	gotoxy(BOARDX + 2, BOARDY - 2);
	cputs("Ilosc:");
	gotoxy(BOARDX + size + 2, BOARDY - 1);
	cputs("0:");
	gotoxy(BOARDX + size + 5, BOARDY - 1);
	cputs("1:");
	int i;
	for (i = 0; i < size; ++i)
	{
		int number_zero_row = 0;
		int number_one_row = 0;
		int number_zero_column = 0;
		int number_one_column = 0;
		int j;
		for (j = 0; j < size; ++j)
		{
			if (board[i][j].value == '0')
			{
				++number_zero_row;
			}
			if (board[i][j].value == '1')
			{
				++number_one_row;
			}
			if (board[j][i].value == '0')
			{
				++number_zero_column;
			}
			if (board[j][i].value == '1')
			{
				++number_one_column;
			}
		}
		char txt[3];
		sprintf(txt, "%d", number_zero_row);
		gotoxy(BOARDX + size + 2, BOARDY + 1 + i);
		cputs(txt);
		gotoxy(BOARDX + size + 5, BOARDY + 1 + i);
		sprintf(txt, "%d", number_one_row);
		cputs(txt);

		sprintf(txt, "%d", number_zero_column);
		gotoxy(BOARDX + 1 + i, BOARDY + size + 2);
		cputs(txt);
		gotoxy(BOARDX + 1 + i, BOARDY + size + 4);
		sprintf(txt, "%d", number_one_column);
		cputs(txt);
	}


	gotoxy(tempx, tempy);
}