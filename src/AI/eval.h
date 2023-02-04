#ifndef EVAL_H
#define EVAL_H
#include "Node.h"

#define SINGLE_VALUE 150
#define DOUBLE_VALUE 250
#define MIXED_VALUE 350
#define GOAL_VALUE 1000000

#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)

static unsigned int lookup[256] = {COUNT_BITS};

static int single_table[8][8] = {{0, GOAL_VALUE, GOAL_VALUE, GOAL_VALUE, GOAL_VALUE, GOAL_VALUE, GOAL_VALUE, 0},
                                 {50, 50, 50, 50, 50, 50, 50, 50},
                                 {10, 10, 20, 30, 30, 30, 10, 10},
                                 {5, 5, 10, 25, 25, 10, 5, 5},
                                 {0, 0, 0, 20, 20, 0, 0, 0},
                                 {5, -5, -10, 0, 0, 10, -5, 5},
                                 {5, 10, 10, -20, -20, 10, 10, 5},
                                 {0, 0, 0, 0, 0, 0, 0, 0}};
static int double_table[8][8] = {{0, GOAL_VALUE, GOAL_VALUE, GOAL_VALUE, GOAL_VALUE, GOAL_VALUE, GOAL_VALUE, 0},
                                 {50, 50, 50, 60, 60, 50, 50, 50},
                                 {50, 50, 60, 60, 60, 60, 50, 50},
                                 {-30, 5, 15, 20, 20, 15, 5, -30},
                                 {-30, 0, 15, 20, 20, 15, 0, -30},
                                 {-30, 5, 10, 15, 15, 10, 5, -30},
                                 {-40, -20, 0, 5, 5, 0, -10, -40},
                                 {0, -40, -30, -30, -30, -30, -40, 0}};

int evalBoard(Node* n, char maxplayer);
unsigned int count_set_bits(unsigned long long int board);
int get_position_value_white(unsigned long long int wb, char type);
int get_position_value_black(unsigned long long int bb, char type);
unsigned int opponent_can_slay(Node *n, char player);

#endif //EVAL_H
