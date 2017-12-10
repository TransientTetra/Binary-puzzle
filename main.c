#include <stdio.h>
#include "conio2.h"
#include "draw.h"
#include "memory.h"
#include "rules.h"

int main(int argc, char const *argv[])
{
	Conio2_Init();
	
	int x = 0, y = 0;
	struct field **board;
	int size_board = 12;
	int pressed_key = 0;
	
	settitle("Mikolaj Sperkowski 171725");
	board = make_table(size_board);
	init_table(board, size_board);
	
	textbackground(BLUE);
	clrscr();
	textcolor(WHITE);
	
	draw_board(board, size_board, BOARDX, BOARDY);
	draw_instruction(x, y);
	
	gotoxy(BOARDX + 1, BOARDY + 1);

	do
	{
		int clr = 1;
		reset_rules(board, size_board);
		check_rules(board, size_board);

		pressed_key = getch();
		
		if (pressed_key == 0)
		{
			pressed_key = getch();
			switch (pressed_key)
			{
				case LEFT_ARROW:
					move_left(&y);
					break;
				case DOWN_ARROW:
					move_down(&x, size_board);
					break;
				case UP_ARROW:
					move_up(&x);
					break;
				case RIGHT_ARROW:
					move_right(&y, size_board);
					break;
			}
		}
		else
		{
			switch (pressed_key)
			{
				case ZERO_KEY:
					if (board[x][y].initialized != 1)
					{
						if (board[x][y].possiblezero == 1)
						{
							board[x][y].value = '0';
							board[x][y].filled = 1;
						}
					}
					break;
					
				case ONE_KEY:
					if (board[x][y].initialized != 1)
					{
						if (board[x][y].possibleone == 1)
						{
							board[x][y].value = '1';
							board[x][y].filled = 1;
						}
					}
					break;

				case N_KEY:
				case N_BIG_KEY:
					del_table(board, size_board);
					size_board = 12;
					board = make_table(size_board);
					init_table(board, size_board);
					x = 0;
					y = 0;
					gotoxy(BOARDX + 1, BOARDY + 1);
					break;

				case O_KEY:
				case O_BIG_KEY:
					partial_random_fill(board, size_board);
					break;

				case P_KEY:
				case P_BIG_KEY:
					clrscr();
					draw_board(board, size_board, BOARDX, BOARDY);
					easy_hint(board, x, y);
					clr = 0;
					break;

				case R_KEY:
				case R_BIG_KEY:
					board = resize_board(&size_board, &x, &y);
					check_rules(board, size_board);
					break;

				case K_KEY:
				case K_BIG_KEY:
					simple_check_win(board, size_board);
					clr = 0;
					break;

				case D_KEY:
				case D_BIG_KEY:
					clrscr();
					draw_board(board, size_board, BOARDX, BOARDY);
					display_amount(board, size_board);
					clr = 0;
					break;
			}
		}
		if (clr == 1) clrscr();
		if (clr == 1) draw_board(board, size_board, BOARDX, BOARDY);
		draw_instruction(x, y);
				

	}while(pressed_key != ESCAPE_KEY);

	del_table(board, size_board);
	return 0;
}
