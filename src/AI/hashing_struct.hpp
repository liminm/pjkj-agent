#include "Node.h"

typedef struct HashNode {
    Node *current;
    char next_move[5];
    //hashing
    unsigned long long int id;
    UT_hash_handle hh;
} HashNode;
