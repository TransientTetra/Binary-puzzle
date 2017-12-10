//func makes a mallocated table of size n of field structs, returns ptr to it
struct field ** make_table(int n);

//frees up mallocated previously table
void del_table(struct field ** table, int size);

//func initializes the table from the init file which contains
//the given initial config of table
void init_table(struct field ** board, int size);

//func fills the board with random number of randomly chosen ones and
//zeroes which fulfill the rules
void partial_random_fill(struct field **board, int size);

//this func deletes current board, asks for size between
//min board size and what screen allows and creates new one
//randomly filled
struct field ** resize_board(int *size, int *x, int *y);