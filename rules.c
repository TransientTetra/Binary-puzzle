#include "draw.h"
#include "rules.h"
#include "memory.h"

//checks all cells if putting 1 or 0 is possible and changes
//struct element possibleone and possiblezero accordingly
void check_rules(struct field **board, int size)
{
	//this section checks for first rule
	{
		int i;
		for (i = 0; i < size; ++i)
		{
			int j;
			for (j = 0; j < size; ++j)
			{
				if (board[i][j].initialized != 1)
				{
					char temp = board[i][j].value;
					
					board[i][j].value = '0';
					if (check_one(board, size) == 1)
					{
						board[i][j].possiblezero = 0;
						board[i][j].reason_zero = 1;
					}
					
				
					board[i][j].value = '1';
					if (check_one(board, size) == 1)
					{
						board[i][j].possibleone = 0;
						board[i][j].reason_one = 1;
					}
				
					board[i][j].value = temp;
				}
			}
		}
	}

	//this section checks for second rule
	{
		int i;
		for (i = 0; i < size; ++i)
		{
			int j;
			int onecount = 0;
			int zerocount = 0;
	
			for (j = 0; j < size; ++j)
			{
				if (board[i][j].value == '0') ++zerocount;
				if (board[i][j].value == '1') ++onecount;
			}
	
			if (zerocount + onecount >= size - 1)
			{
				if (onecount > zerocount)
				{
					int k;
					for (k = 0; k < size; ++k)
					{
						board[i][k].possibleone = 0;
						board[i][k].reason_one = 2;
					}
				}
		
				else if (onecount < zerocount)
				{
					int k;
					for (k = 0; k < size; ++k)
					{
						board[i][k].possiblezero = 0;
						board[i][k].reason_zero = 2;
					}
				}
			}
		}
	
		for (i = 0; i < size; ++i)
		{
			int j;
			int onecount = 0;
			int zerocount = 0;
	
			for (j = 0; j < size; ++j)
			{
				if (board[j][i].value == '0') ++zerocount;
				if (board[j][i].value == '1') ++onecount;
			}
			if (zerocount + onecount >= size - 1)
			{
				if (onecount > zerocount)
				{
					int k;
					for (k = 0; k < size; ++k)
					{
						board[k][i].possibleone = 0;
						board[k][i].reason_one = 2;
					}
				}
		
				else if (onecount < zerocount)
				{
					int k;
					for (k = 0; k < size; ++k)
					{
						board[k][i].possiblezero = 0;
						board[k][i].reason_zero = 2;
					}
				}
			}			
		}
	}

	//this section checks for third rule
	{
		int i;
		for (i = 0; i < size; ++i)
		{
			int j;
			for (j = 0; j < size; ++j)
			{
				if (board[i][j].initialized != 1)
				{
					char temp = board[i][j].value;
					
					board[i][j].value = '0';
					if (check_three(board, size) == 1)
					{
						board[i][j].possiblezero = 0;
						board[i][j].reason_zero = 3;
					}
				
				
					board[i][j].value = '1';
					if (check_three(board, size) == 1)
					{
						board[i][j].possibleone = 0;
						board[i][j].reason_one = 3;
					}
				
					board[i][j].value = temp;
				}
			}
		}
	}

	//this makes all preinitialized fields impossible to fill
	{
		int i;
		for (i = 0; i < size; ++i)
		{
			int j;
			for (j = 0; j < size; ++j)
			{
				if (board[i][j].initialized == 1)
				{
					board[i][j].possiblezero = 0;
					board[i][j].possibleone = 0;
					board[i][j].reason_zero = 4;
					board[i][j].reason_one = 4;
				}
			}
		}
	}
}

//this func resets possibilities
void reset_rules(struct field **board, int size)
{
	int i;
	for (i = 0; i < size; ++i)
	{
		int j;
		for (j = 0; j < size; ++j)
		{
			board[i][j].possibleone = 1;
			board[i][j].possiblezero = 1;
			board[i][j].reason_one = 0;
			board[i][j].reason_zero = 0;
		}
	}
}

//this func checks rows and columns, returns 1 if there are identical rows or columns, 0 otherwise
int check_three(struct field **board, int size)
{
	int chck = 0;
	int i;
	for (i = 0; i < size; ++i)
	{
		int blank = 0;
		int k;
		for (k = 0; k < size; ++k)
		{
			if (k != i)
			{
				int j;
				for (j = 0; j < size; ++j)
				{
					if (board[i][j].value == '1' || board[i][j].value == '0') ++blank;
					if (board[i][j].value != board[k][j].value) break;
					else if (board[i][j].value == board[k][j].value && j == size - 1 && blank > 0)
					{
						++chck;
					}
				}
			}
		}
	}
	for (i = 0; i < size; ++i)
	{
		int blank = 0;
		int k;
		for (k = 0; k < size; ++k)
		{
			if (k != i)
			{
				int j;
				for (j = 0; j < size; ++j)
				{

					if (board[j][i].value == '1' || board[j][i].value == '0') ++blank;
					if (board[j][i].value != board[j][k].value) break;
					else if (board[j][i].value == board[j][k].value && j == size - 1 && blank > 0)
					{
						++chck;
					}
				}
			}
		}
	}

	return (chck > 0)?1:0;
}

//checks if there are more than two ones or zeroes beside each other
//returns 0 if there are not, 1 if there are
int check_one(struct field **board, int size)
{
	int i;
	for (i = 0; i < size; ++i)
	{
		int countzero = 0;
		int countone = 0;
		int j;
		for (j = 0; j < size; ++j)
		{
			if (board[i][j].value == '0') ++countzero;
			if (board[i][j].value == '1') ++countone;
			if (countone > 2 || countzero > 2) return 1;
			if (board[i][j].value != '0')
			{
				countzero = 0;
			}
			if (board[i][j].value != '1')
			{
				countone = 0;
			}
		}
	}

	for (i = 0; i < size; ++i)
	{
		int countzero = 0;
		int countone = 0;
		int j;
		for (j = 0; j < size; ++j)
		{
			if (board[j][i].value == '0') ++countzero;
			if (board[j][i].value == '1') ++countone;
			if (countone > 2 || countzero > 2) return 1;
			if (board[j][i].value != '0')
			{
				countzero = 0;
			}
			if (board[j][i].value != '1')
			{
				countone = 0;
			}
		}
	}
	return 0;
}
