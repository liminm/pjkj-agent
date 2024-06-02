#include "time_count.h"
#include "src/AI/Node.h"
#include "src/AI/parseFen.h"
#include "src/AI/move_generator.h"
#include "test_boards.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gcc -o mg_time mg_time_test.c parseFen.c time_count.c move_generator.c -lm
// ./mg_time 100 > mg_time_log.txt
// mit n= 1000000 ca 4min laufzeit

void freemoves(unsigned long long int ***moves){
    for(int i=0;i<12;i++){
        for(int j=0;j<5;j++){
            free(moves[i][j]);
        }
        free(moves[i]);
    }
    free(moves);
}

int main(int argc, char *argv[]) {
    //printf("Argc: %d\n", argc);
    int loop;

    if(argc == 1){
        loop = 10000;
        //printf("0\n");
    } else if ( argc == 2){
        loop = atoi(argv[1]);
        //printf("%d\n", loop);
    } else {
        printf("Error: Wrong input!\n");
        return -1;
    }
    
    /*char player = 'b';
    //calculate move
    char fen[] = "1bbbbbb1/1bbbbbb1/8/8/8/8/1BBBBBB1/1BBBBBB1 b - - 0 1";
    Node *node = parseFEN(fen);
    node->value = -1;

    if(player == 'w'){
        node->player = 0;
    } else{
        node->player = 1;
    }*/

    long time_avg;
    long time_avg_all = 0;

    unsigned long long int ***moves;

    long time_start;
    long time_end;

    char *fen;
    char player;
    Node *node;

    printf("Random boards\n");
    for (int k=0; k<20; ++k){

        time_avg = 0;

        fen= malloc(sizeof(char) * 80); // +1 for the null-terminator
        // in real code you would check for errors in malloc here
        strcpy(fen, arr1[k]);
        node = parseFEN(fen);
        node->value = -1;
        player = 'b';
        if(player == 'w'){
            node->player = 0;
        } else{
            node->player = 1;
        }

        for (int i = 1; i<=loop; ++i){
            //count time for move generation
            time_start = get_nanos();
            moves = calcmovesboard(node->sw, node->sb, node->dw, node->db, node->mw, node->mb, node->player);
            time_end = get_nanos();
            time_avg =  time_avg + (time_end - time_start);

            freemoves(moves);
        }
        time_avg_all += time_avg;
        time_avg = time_avg / loop;

        printf("FEN: %s\n", fen);
        printf("Function run %d times\n", loop);
        printf("Diff in nano sec: %ld\n\n", time_avg);
        free(fen);
    }
    time_avg_all = time_avg_all/(20*loop);
    printf("Time average for arr1: %ld\n\n", time_avg_all);

    time_avg_all = 0;
    printf("\n1 white figure\n");

    for (int k=0; k<20; ++k){
        
        time_avg = 0;

        fen= malloc(sizeof(char) * 80); // +1 for the null-terminator
        // in real code you would check for errors in malloc here
        strcpy(fen, arr2[k]);
        node = parseFEN(fen);
        node->value = -1;
        player = 'b';
        if(player == 'w'){
            node->player = 0;
        } else{
            node->player = 1;
        }

        for (int i = 1; i<=loop; ++i){
            //count time for move generation
            time_start = get_nanos();
            moves = calcmovesboard(node->sw, node->sb, node->dw, node->db, node->mw, node->mb, node->player);
            time_end = get_nanos();
            time_avg =  time_avg + (time_end - time_start);

            freemoves(moves);
        }

        time_avg_all += time_avg;
        time_avg = time_avg / loop;

        printf("FEN: %s\n", fen);
        printf("Function run %d times\n", loop);
        printf("Diff in nano sec: %ld\n\n", time_avg);
        free(fen);
    }
    time_avg_all = time_avg_all/(20*loop);
    printf("Time average for arr2: %ld\n\n", time_avg_all);

    time_avg_all = 0;
    printf("\n12 white figures\n");

    for (int k=0; k<20; ++k){

        time_avg = 0;

        fen= malloc(sizeof(char) * 80); // +1 for the null-terminator
        // in real code you would check for errors in malloc here
        strcpy(fen, arr3[k]);
        node = parseFEN(fen);
        node->value = -1;
        player = 'b';
        if(player == 'w'){
            node->player = 0;
        } else{
            node->player = 1;
        }

        for (int i = 1; i<=loop; ++i){
            //count time for move generation
            time_start = get_nanos();
            moves = calcmovesboard(node->sw, node->sb, node->dw, node->db, node->mw, node->mb, node->player);
            time_end = get_nanos();
            time_avg =  time_avg + (time_end - time_start);

            freemoves(moves);
        }
        
        time_avg_all += time_avg;
        time_avg = time_avg / loop;

        printf("FEN: %s\n", fen);
        printf("Function run %d times\n", loop);
        printf("Diff in nano sec: %ld\n\n", time_avg);
        free(fen);
    }
    time_avg_all = time_avg_all/(20*loop);
    printf("Time average for arr3: %ld\n\n", time_avg_all);
    /*
    time_avg = time_avg / loop;

    //get execution time of move_generator
    long diff_nanos = time_avg;
    long diff_milli = diff_nanos / 1000000;
    int diff_sec = diff_milli / 1000;
    //print average calculation time move_generator
    printf("Function run %d times\n", loop);
    printf("Diff in nano sec: %ld\n", diff_nanos);
    printf("Diff in milli sec: %ld\n", diff_milli);
    printf("Diff in sec: %d\n\n", diff_sec);
    */

    return 1;
}