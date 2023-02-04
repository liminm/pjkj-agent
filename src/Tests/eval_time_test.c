#include "time_count.h"
#include "src/AI/Node.h"
#include "src/AI/parseFen.h"
#include "src/AI/eval.h"
#include "test_boards.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gcc -o eval_time_test eval_time_test.c parseFen.c time_count.c eval.c -lm
// ./eval_time 100 > eval_time_log.txt

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

    long time_avg;
    long time_avg_all = 0;

    char maximizingPlayer = 0;
    int value = 0;

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
            value = evalBoard(node, maximizingPlayer);
            time_end = get_nanos();
            time_avg =  time_avg + (time_end - time_start);
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

    printf("1 white figure\n");
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
            value = evalBoard(node, maximizingPlayer);
            time_end = get_nanos();
            time_avg =  time_avg + (time_end - time_start);
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

    printf("12 white figures\n");
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
            value = evalBoard(node, maximizingPlayer);
            time_end = get_nanos();
            time_avg =  time_avg + (time_end - time_start);
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

    /*char player = 'b';
    //calculate move
    char fen[] = "1bbbbbb1/1bbbbbb1/8/8/8/8/1BBBBBB1/1BBBBBB1 b - - 0 1";
    Node *node = parseFEN(fen);
    node->value = -1;
    if(player == 'w'){
        node->player = 0;
    } else{
        node->player = 1;
    }

    long time_avg = 0;
    int value = 0;
    int loop = 10000000;
    char maximizingPlayer = 1;

    for (int i = 1; i<=loop; ++i){
        //count time for move generation
        long time_start = get_nanos();
        value = evalBoard(node, maximizingPlayer);
        long time_end = get_nanos();
        time_avg =  time_avg + (time_end - time_start);

    }

    time_avg = time_avg / loop;

    //get execution time of move_generator
    long diff_nanos = time_avg;
    long diff_milli = diff_nanos / 1000000;
    int diff_sec = diff_milli / 1000;
    //print average calculation time move_generator
    printf("Function run %d times\n", loop);
    printf("Diff in nano sec: %ld\n", diff_nanos);
    printf("Diff in milli sec: %ld\n", diff_milli);
    printf("Diff in sec: %d\n\n", diff_sec);*/

    return 1;
}