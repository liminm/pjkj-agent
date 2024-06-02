#include <stdio.h>
#include "Node.h"
#include "parseFen.h"
#include "get_move_as_string.h"
#include "move_generator.h"

int main(int argc, char *argv[]) {
    if(argc != 4){
        return -1;
    }
    char* fen = argv[1];
    char player = argv[2][0];
    char *ptr;
    unsigned long int rnd_num = strtol(argv[3], &ptr, 10);

    /*char fen[] = "1bbbbbb1/1bbbbbb1/8/8/8/8/1BBBKBB1/1BBB1BB1 b - - 1 1";
    char player = 'b';*/

    Node *node = parseFEN(fen);
    node->value = -1;
    if(player == 'w'){
        node->player = 0;
    } else{
        node->player = 1;
    }

    unsigned long long int*** moves = calcmovesboard(node->sw, node->sb, node->dw, node->db, node->mw, node->mb, node->player);
    unsigned long long int** valid_moves;


    valid_moves = calloc(12*5,sizeof(unsigned long long int**));

    for(int i=0;i<12*5;i++){
        valid_moves[i] = calloc(6,sizeof(unsigned long long int*));
    }

    int moveCount = 0;
    int count = 0;

    for (int i=0; i < 12; i++){
        count = 0;
        for (int j=0; j < 5; j++){
            if (count_set_bits(moves[i][j][0] ^ moves[i][j][1] ^ moves[i][j][2] ^ moves[i][j][3] ^ moves[i][j][4] ^ moves[i][j][5]) != 0){
                valid_moves[moveCount][0] = moves[i][j][0];
                valid_moves[moveCount][1] = moves[i][j][1];
                valid_moves[moveCount][2] = moves[i][j][2];
                valid_moves[moveCount][3] = moves[i][j][3];
                valid_moves[moveCount][4] = moves[i][j][4];
                valid_moves[moveCount][5] = moves[i][j][5];
            }
            else{
                moveCount --;
                count ++;
            }
            moveCount++;
        }
        if (count == 5){
            break;
        }
    }
    unsigned int rand_num = rnd_num % moveCount;

    Node *move = (Node*) malloc(sizeof(Node));

    move->sw = valid_moves[rand_num][0];
    move->sb = valid_moves[rand_num][1];
    move->dw = valid_moves[rand_num][2];
    move->db = valid_moves[rand_num][3];
    move->mw = valid_moves[rand_num][4];
    move->mb = valid_moves[rand_num][5];


    char* move_string = get_move_new(node, move, node->player);

    printf("%s", move_string);

    return 0;
}