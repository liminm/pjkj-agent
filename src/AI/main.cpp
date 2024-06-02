#include <stdio.h>
#include "parseFen.h"
#include "Node.h"
#include "ab-cut.h"
#include "get_move_as_string.h"
#include "hash_functions.h"

int main(int argc, char *argv[]) {
    if(argc != 4){
        return -1;
    }
    char* fen = argv[1];
    char player = argv[2][0];
    int depth = argv[3][0] - '0';

    /*char player = 'b';
    int depth = 7;
    char fen[] = "1bbbbbb1/1bbbbbb1/8/8/8/8/1BBBBKB1/1BBBB1B1 b - - 1 1";*/

    Node *node = parseFEN(fen);
    node->value = -1;
    if(player == 'w'){
        //printf("w\n");
        node->player = 0;
    } else{
        // printf("b\n");
        node->player = 1;
    }
    

    //initialize hashmap
    /*hashmap = NULL;
    populate_hashmap();
    HashNode *erg = find_node_in_hashmap(hash_node(node));
    //if not in hashmap continue with alpha beta cutoff
    if (erg != NULL) {
        //TODO muss \0 vom string vor dem return entfernen
        //printf("%s", erg->next_move);
        return erg->next_move;
    }*/

    Node *result = alphabeta(node, depth, INT_MIN, INT_MAX, '1');

    Node *move = result;
    for(int i = 0; i < depth-1; i++){
        move = move->next_move;
    }

    char* move_string = get_move_new(node, move, node->player);

    printf("%s", move_string);

    return 0;
}

