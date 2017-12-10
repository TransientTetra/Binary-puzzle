//checks all cells if putting 1 or 0 is possible and changes
//struct element possibleone and possiblezero accordingly
void check_rules(struct field **board, int size);

//this func checks rows and columns, returns 1 if there are identical rows or columns, 0 otherwise
int check_three(struct field **board, int size);

//checks if there are more than two ones or zeroes beside each other
//returns 0 if there are not, 1 if there are
int check_one(struct field **board, int size);

//this func resets possibilities
void reset_rules(struct field **board, int size);
