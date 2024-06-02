#ifndef AB_CUT_H
#define AB_CUT_H

#define lower_intervallimit 4
#define upper_intervallimit 61

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "Node.h"
#include "compare.h"
#include "eval.h"
#include "quicksort.h"
#include "move_generator.h"

Node *alphabeta(Node *node, int depth, int alpha, int beta, char maximizingPlayer);
Node *generate_node(Node *next_move, unsigned long long int sw, unsigned long long int sb, unsigned long long int dw, unsigned long long int db, unsigned long long int mw, unsigned long long int mb);
void freemoves(unsigned long long int ***moves);
//void printBits(size_t const size, void const * const ptr);

#endif //_CUT_H
