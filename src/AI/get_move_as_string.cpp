#include "get_move_as_string.h"

char * get_move_new(Node *root, Node *next_move, char player){
    unsigned long long int post_s;
    unsigned long long int post_d;
    unsigned long long int post_m;
    unsigned long long int pre_s;
    unsigned long long int pre_d;
    unsigned long long int pre_m;
    unsigned long long start;
    unsigned long long end;

    if(player){
        pre_s = root->sb;
        post_s = next_move->sb;
        pre_d = root->db;
        post_d = next_move->db;
        pre_m = root->mb;
        post_m = next_move->mb;
    }
    else{
        pre_s = root->sw;
        post_s = next_move->sw;
        pre_d = root->dw;
        post_d = next_move->dw;
        pre_m = root->mw;
        post_m = next_move->mw;
    }

    //s=single; b=double; m=mixed

    char* move;
    //ss : single to single
    start = (pre_s^post_s) &pre_s;
    end = (pre_s^post_s) &post_s;

    if ((count_set_bits(start) + count_set_bits(end))== 2 && count_set_bits((post_d ^ pre_d) ^ (pre_m ^ post_m)) == 0) {
        move = get_next_move_as_string( start, end );
        return move;
    }
    //sm
    start = (pre_s^post_s);
    end = (pre_m ^ post_m);

    if ((count_set_bits(post_s) < count_set_bits(pre_s)) && (count_set_bits(start) + count_set_bits(end))== 2 && count_set_bits((post_d ^ pre_d)) == 0) {
        move = get_next_move_as_string( start, end );
        return move;
    }
    //sd
    end = (pre_d ^ post_d);
    start = (pre_s ^ post_s) ^ end;

    if ((count_set_bits(post_s) < count_set_bits(pre_s)) && (count_set_bits(start) + count_set_bits(end))== 2 && (count_set_bits((post_m ^ pre_m)) == 0)) {
        move = get_next_move_as_string( start, end );
        return move;
    }
    //ds
    start = pre_d ^ post_d;
    end = (pre_s ^ post_s) ^ start;

    if ((count_set_bits(post_d) < count_set_bits(pre_d)) && (count_set_bits(start) + count_set_bits(end))== 2 && (count_set_bits((post_m ^ pre_m)) == 0)) {
        move = get_next_move_as_string( start, end );
        return move;
    }
    //dd
    end = (pre_d^post_d) &post_d;
    start = (pre_d^post_d) &pre_d;

    if ((count_set_bits(start) + count_set_bits(end))== 2 && count_set_bits((pre_m ^ post_m)) == 0) {
        move = get_next_move_as_string( start, end );
        return move;
    }
    //mm
    end = (pre_m^post_m) &post_m;
    start = (pre_m^post_m) &pre_m;

    if ((count_set_bits(start) + count_set_bits(end))== 2 && count_set_bits((post_d ^ pre_d) ^ (pre_s ^ post_s)) == 0) {
        move = get_next_move_as_string( start, end );
        return move;
    }
    //dm
    start = pre_d ^ post_d;
    end = pre_m ^ post_m;

    if ((count_set_bits(post_d) < count_set_bits(pre_d)) && (count_set_bits(start) + count_set_bits(end))== 2 ) {
        move = get_next_move_as_string( start, end );
        return move;
    }
    //md
    start = pre_m ^ post_d;
    end = pre_d ^ post_d;

    if ((count_set_bits(post_m) < count_set_bits(pre_m)) && (count_set_bits(start) + count_set_bits(end))== 2 && count_set_bits((post_s ^ pre_s)) == 0) {
        move = get_next_move_as_string( start, end );
        return move;
    }
    //ms
    start = pre_m ^ post_m;
    end = pre_s ^ post_s;

    if ((count_set_bits(post_m) < count_set_bits(pre_m)) && (count_set_bits(start) + count_set_bits(end))== 2 && count_set_bits((post_d ^ pre_d)) == 0) {
        move = get_next_move_as_string( start, end );
        return move;
    }
    //s schlägt mixed
    start = pre_s ^ post_s;
    end = pre_d ^ post_d;

    if ((count_set_bits(post_d) > count_set_bits(pre_d)) && (count_set_bits(start) + count_set_bits(end))== 2 && (count_set_bits((post_m ^ pre_m)) == 0)) {
        move = get_next_move_as_string( start, end );
        return move;
    }

    return move;

}

char* get_next_move_as_string( unsigned long long int bitboard_pre, unsigned long long int bitboard_post ){

    char * start = get_position(bitboard_pre);
    char * end = get_position(bitboard_post);

    //printBits(8, &bitboard_pre);
    //printBits(8, &bitboard_post);

    char *move= malloc(strlen(start) + strlen(end) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(move, start);
    strcat(move, end);

    //free(start);
    //free(end);

    return move;
}

char * get_position(unsigned long long int bitboard){
    /*
        Traverse bitboard from index 0 - 63 (right to left / bottom to top)
    */
    char * pos = malloc(sizeof(char)*3);
    pos[2] = '\0';

    unsigned int count = 0;

    while (bitboard) {
            if ( bitboard & 1 ){
                char column_char = 104; //104 - h
                unsigned int row = 49 + ( count / 8 );
                unsigned int column = count % 8;

                column_char = column_char - column;
                pos[0] = column_char;
                pos[1] = row;

                //printf("X: %c%c\n", column_char, row);
                break;
            }
            count += 1;
            bitboard >>= 1;
        }

    return pos;
}