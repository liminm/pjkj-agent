#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "eval.h"
#include "Node.h"

char* get_next_move_as_string( unsigned long long int bitboard_pre, unsigned long long int bitboard_post );
char * get_position(unsigned long long int bitboard);
char * get_move_new(Node *root, Node *next_move, char player);