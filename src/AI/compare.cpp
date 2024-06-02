#include "compare.h"

Node *get_max_Node(Node *a, Node *b){
    if ( a->value >= b->value){
        if (b->children != NULL){
            free(b->children);
        }
        free(b);
        return a;
    }
    else{
        if (a->children != NULL){
            free(a->children);
        }
        free(a);
        return b;
    }
}

Node *get_min_Node(Node *a, Node *b){
    if ( a->value <= b->value){
        if (b->children != NULL){
            free(b->children);
        }
        free(b);
        return a;
    }
    else{
        if (a->children != NULL){
            free(a->children);
        }
        free(a);
        return b;
    }
}

int get_max_Value(int a, int b){
    if ( a >= b){
        return a;
    }
    else{
        return b;
    }
}

int get_min_Value(int a, int b){
    if ( a <= b){
        return a;
    }
    else{
        return b;
    }
}