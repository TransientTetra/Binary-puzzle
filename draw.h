#define INSTRUCTIONORIENT 1 //leftmost corner of instructions, x

#define MINIMAL_BOARD_SIZE 2
#define INSTRUCTION_WIDTH 52
#define POPUP_HEIGHT 6

#define BOARDX 52 //upperleft corner of board, x
#define BOARDY 6 //upperleft corner of board, y

#define ESCAPE_KEY 27
#define BACKSPACE_KEY 8
#define LEFT_ARROW 0x4b
#define RIGHT_ARROW 0x4d
#define UP_ARROW 0x48
#define DOWN_ARROW 0x50
#define ZERO_KEY 48
#define ONE_KEY 49
#define N_KEY 110
#define N_BIG_KEY 78
#define O_KEY 111
#define O_BIG_KEY 79
#define P_KEY 112
#define P_BIG_KEY 80
#define R_KEY 114
#define R_BIG_KEY 82
#define K_KEY 107
#define K_BIG_KEY 75
#define D_KEY 100
#define D_BIG_KEY 68
#define A_KEY 97
#define A_BIG_KEY 65
#define J_KEY 106
#define J_BIG_KEY 74
#define S_KEY 115
#define S_BIG_KEY 83
#define L_KEY 76
#define L_BIG_KEY 101
#define B_KEY 98
#define B_BIG_KEY 66

struct field
{
	int filled;
	char value;
	int initialized;
	int possibleone;
	int possiblezero;
	int reason_zero;
	int reason_one;
};

//func draws a horizontal line in point(x, y) that is n long
void draw_horizontal_line(int x, int y, int n);

//func draws a vertical line
void draw_vertical_line(int x, int y, int n);

//func draws instructions and completed points and author's name
void draw_instruction(int x, int y);

//func draws board, last two arguments specify the leftmost corner
void draw_board(struct field ** board, int size_board, int startx, int starty);


//movement funcs
void move_up(int *y);

void move_down(int *y, int size_board);

void move_left(int *x);

void move_right(int *x, int size_board);


//displays an easy hint in instruction region
void easy_hint(struct field **board, int x, int y);

//highlights these fields that neither one nor zero can be put in
void simple_check_win(struct field **board, int size);

//this func displays the number of zeroes and ones in each row and column
//next to said row or column
void display_amount(struct field **board, int size);