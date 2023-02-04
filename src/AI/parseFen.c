#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Node.h"

Node* parseFEN(const char *fen){
    Node *n = malloc(sizeof(Node));
    n->sw = 0; // B
    n->sb = 0; // b
    n->dw = 0; // K
    n->db = 0; // k
    n->mw = 0; // Q
    n->mb = 0; // q

    int pos = 0; //board position
    char c = fen[pos];

    int i = 0; //string position

    while (c != '\0'){
        if(c == ' '){
            break;
        }

        unsigned long long int mask = 0;
        mask |= 1ULL << (63 - pos);


        if (isdigit(c)){
            pos += (c - '0');
            i ++;
            c = fen[i];
        }
        else if (c == '/'){
            i ++;
            c = fen[i];
        }
        else if (c == 'B'){
            n->sw |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'b' && pos < 64){
            n->sb |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'Q'){
            n->mw |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'q'){
            n->mb |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'K'){
            n->dw |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'k'){
            n->db |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else{
            i ++;
            c = fen[i];
        }


    }
    n->value = 0;

    return n;
}

