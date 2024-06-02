#include <limits.h>
#include "uthash.h"

#ifndef NODE_H
#define NODE_H

#define FEN_MAXSIZE 92
#define MAX_CHILDREN 60

typedef struct Node {
    struct Node *next_move;
    //Bitboards
    unsigned long long int sw;
    unsigned long long int sb;
    unsigned long long int dw;
    unsigned long long int db;
    unsigned long long int mw;
    unsigned long long int mb;

    int value;
    struct Node **children;
    char player; //0: white, 1: black
} Node;

#endif //NODE_H
