#include "ab-cut.h"

void freemoves(unsigned long long int ***moves){
    for(int i=0;i<12;i++){
        for(int j=0;j<5;j++){
            free(moves[i][j]);
        }
        free(moves[i]);
    }
    free(moves);
}

Node* generate_node(Node* next_move, unsigned long long int sw, unsigned long long int sb, unsigned long long int dw, unsigned long long int db, unsigned long long int mw, unsigned long long int mb){
    Node* node = new Node;
    if (node == nullptr) {
        printf("Error: malloc initialized Node with NULL\n");
        return nullptr;
    }

    node->children = nullptr;
    node->next_move = next_move;

    //bitboards
    node->sw = sw;
    node->sb = sb;
    node->dw = dw;
    node->db = db;
    node->mw = mw;
    node->mb = mb;

    node->value = 0;

    return node;
}

Node* alphabeta(Node* node, int depth, int alpha, int beta, char maximizingPlayer){

    if (depth == 0){
        //printf("%d\n", node->value);
        return node;
    }
    unsigned long long int*** moves = calcmovesboard(node->sw, node->sb, node->dw, node->db, node->mw, node->mb, node->player);
    int moveCount = 0;
    int count = 0;
    node->children = new Node*[numMoves+1];

    for (int i=0; i < 12; i++){
        count = 0;
        for (int j=0; j < 5; j++){
            if (count_set_bits(moves[i][j][0] ^ moves[i][j][1] ^ moves[i][j][2] ^ moves[i][j][3] ^ moves[i][j][4] ^ moves[i][j][5]) != 0){
                Node* child = generate_node(nullptr, moves[i][j][0], moves[i][j][1],
                                            moves[i][j][2], moves[i][j][3], moves[i][j][4], moves[i][j][5]);
                child->player = !(node->player);
                child->value = evalBoard(child, maximizingPlayer);
                node->children[moveCount] = child;

                //add next_move
                //only root has value -1
                /*if (node->value > -1){
                    child->next_move = node->next_move;
                }
                else{
                    child->next_move = child;
                }*/
                child->next_move = node;
            }
            else{
                //node->children[moveCount] = NULL;
                moveCount --;
                count ++;
            }
            moveCount++;
        }
        if (count == 5){
            break;
        }
    }

    node->children[moveCount] = nullptr;

    freemoves(moves);
    if(node->children == nullptr){
        return node;
    }



    // QUICKSORT CALL
    quickSortCall(node,moveCount-1, (maximizingPlayer - '0') );


    if (maximizingPlayer == '1'){
        //printf("Maximizer\n");
        Node* current_node = new Node;
        current_node->value = INT_MIN;
        current_node->children = nullptr;
        //Node *current_node_old = current_node;

        for (int i = 0; i < MAX_CHILDREN; ++i){
            Node* child = node->children[i]; //get next childnode
            if(child == nullptr){
                break;
            }
            //check for ruhesuche
            /*unsigned int ruhig = opponent_can_slay(child, child->player); // 0 - unruhig, 1 - ruhig

            if (ruhig == 0 && depth == 1){
                depth += 1;
            }*/

            current_node = get_max_Node(current_node, alphabeta(child, depth - 1, alpha, beta, '0'));

            alpha = get_max_Value(alpha, current_node->value);

            if (alpha >= beta){
                break;
            }
        }
        /*if(current_node_old != current_node){
            free(current_node_old);
        }*/
        return current_node;
    }
    else { 
        //printf("Minimzer\n");
        Node* current_node = new Node;
        current_node->value = INT_MAX;
        current_node->children = nullptr;
        //Node *current_node_old = current_node;

        
        for (int i = 0; i < MAX_CHILDREN; ++i){
            Node* child = node->children[i]; //get next childnode
            
            if(child == nullptr){
                break;
            }  

            /*unsigned int ruhig = opponent_can_slay(child, child->player); // 0 - unruhig, 1 - ruhig

            if (ruhig == 0 && depth == 1){
                depth += 1;
            }*/

            current_node = get_min_Node(current_node, alphabeta(child, depth - 1, alpha, beta, '1'));

            beta = get_min_Value(beta, current_node->value);

            if (alpha >= beta){
                break;
            }
        }
        /*if(current_node_old != current_node){
            free(current_node_old);
        }*/

        return current_node;
    }
}
