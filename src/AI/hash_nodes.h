#include "Node.h"
#define numberOfNodes 1

/*
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
*/

//UPDATE #define numberOfNodes manually

Node nodes_for_hashpopulation[numberOfNodes] = {
    {NULL, 2149590560, 4923563608874418176, 67115008, 1152921504606846976, 0, 0, 0, NULL, 0}
};
char next_move_string[numberOfNodes][5] = {
    "x5x6"
};
