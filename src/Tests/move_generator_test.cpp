//
// Created by limin on 6/11/20.
//

#include "stdio.h"
//#include "move_generator.h"
#include "src/AI/move_generator.c"
#include "ctype.h"
#include <time.h>
#include <sys/time.h>
#include <stdint.h>



void test(unsigned long long int ***expected, unsigned long long int ***actual,int fignum, const char* testname ){

    int equal = 1;

    // move through moves array
    // set equal to 0 if expected and actual not identical
    int i = fignum;
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 6; k++) {
                if (expected[i][j][k] != actual[i][j][k]) {
                    equal = 0;
                    printf("\n%s FAILED For figure %d for move direction %d for figure type %d\n expected bitboard: %llu\n actual bitboard: %llu\n",testname, i, j, k, expected[i][j][k], actual[i][j][k]);
                }
                //printf("%llu\n",actual[i][j][k]);
            }
        }
    if(equal == 1){
       printf("\n%s PASSED",testname);
    }

}


unsigned long long int *parseFEN(const char *fen){
    char player;
    unsigned long long int *board;
    board = calloc(6,sizeof(unsigned long long int));
    unsigned long long int sw = 0; // B
    unsigned long long int sb = 0; // b
    unsigned long long int dw = 0; // Q
    unsigned long long int db = 0; // q
    unsigned long long int mw = 0; // K
    unsigned long long int mb = 0; // k

    int pos = 0; //board position
    char c = fen[pos];

    int a = 0;
    int i = 0; //string position

    while (c != '\0'){
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
            sw |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'b' && pos < 64){
            if(a == 0){
                sb |= mask;
                pos ++;
                i ++;
                c = fen[i];
            }
        }
        else if (c == 'Q'){
            dw |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'q'){
            db |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'K'){
            mw |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'k'){
            mb |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if(c == '-'){
            a = 1;
            i ++;
            c = fen[i];
        }
        else{
            i ++;
            c = fen[i];
        }
    }


    /*
    while (c != '\0'){
        //printf("\ni: %d FEN Pos: %d c: %c \n",i,pos,c);

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
            sw |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'b' && pos<64){
            //printf("\ni: %d FEN Pos: %d Mask: %llu\n",i,pos,mask);

            sb |= mask;
            //printf("\ni: %d FEN Pos: %d SB: %llu\n",i,pos,sb);
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'Q'){
            dw |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'q'){
            db |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'K'){
            mw |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'k'){
            mb |= mask;
            pos ++;
            i ++;
            c = fen[i];
        }
        else if (c == 'w'){
            player = 1;
            i ++;
            c = fen[i];
        }
        else if (c == 'b' && pos >= 64){
            player = 0;
            i ++;
            c = fen[i];
        }
        else{
            i ++;
            c = fen[i];
        }

    }
     */




    board[0] = sw;
    board[1] = sb;
    board[2] = dw;
    board[3] = db;
    board[4] = mw;
    board[5] = mb;

    return board;
}

unsigned long long int ***ctmatrix(const char *fen0,const char *fen1,const char *fen2,const char *fen3,const char *fen4, int fignum) {

    unsigned long long int ***ctmatrix;
    ctmatrix = calloc(12, sizeof(unsigned long long int **));

    for (int i = 0; i < 12; i++) {
        ctmatrix[i] = calloc(5, sizeof(unsigned long long int *));
        for (int j = 0; j < 5; j++) {
            ctmatrix[i][j] = calloc(6, sizeof(unsigned long long int));
        }
    }

    unsigned long long int *board0;
    board0 = parseFEN(fen0);
    unsigned long long int *board1;
    board1 = parseFEN(fen1);
    unsigned long long int *board2;
    board2 = parseFEN(fen2);
    unsigned long long int *board3;
    board3 = parseFEN(fen3);
    unsigned long long int *board4;
    board4 = parseFEN(fen4);


    for (int j = 0; j < 6; j++) {
        ctmatrix[fignum][0][j] = board0[j];
        ctmatrix[fignum][1][j] = board1[j];
        ctmatrix[fignum][2][j] = board2[j];
        ctmatrix[fignum][3][j] = board3[j];
        ctmatrix[fignum][4][j] = board4[j];
        //printf("%llu\n",board1[0]);
    }


    return ctmatrix;
}

void timer(){

    // random boards
    char arr1[20][80] = {
    "1bbbbbb1/1bbbbbb1/8/8/8/8/1BBBBBB1/1BBBBBB1 w - - 0 1",
    "1b1q1bb1/3bB3/1Bb3q1/2b1QkB1/8/2B5/1B1K1B2/5BB1 w - - 0 1",
    "1bBq1bb1/3b3B/1B1Q2q1/B1b2k2/6B1/4K3/8/3B4 w - - 0 1",
    "1bB3b1/7B/1B3Qq1/B4k2/6B1/2b1K3/6b1/1q1B4 w - - 0 1",
    "1bB3b1/7B/5Q2/B4k2/8/2b5/6b1/1q1B4 w - - 0 1",
    "1b4b1/8/8/B1k5/8/2b1B3/4B1b1/1q1B4 w - - 0 1",
    "1b4b1/8/5B2/2k5/8/2b2B2/6b1/1q1B4 w - - 0 1",
    "1b4b1/8/1Q6/2k5/4Q3/2b5/6b1/1q3Q2 w - - 0 1",
    "1b4b1/8/3K4/K1k5/7K/2b5/6b1/1q2K3 w - - 0 1",
    "1b4b1/8/3K4/K1k5/7Q/2b5/6b1/1q1Q4 w - - 0 1",
    "8/8/6K1/2k2B2/4q1BQ/4B1K1/2b2Qb1/b4b2 w - - 0 1",
    "8/8/B7/B1k5/B3q3/8/2b3b1/b4b2 w - - 0 1",
    "5b2/7B/8/8/8/8/8/8 w - - 0 1",
    "8/1Q6/5B2/8/8/3B4/3B4/b7 w - - 0 1",
    "8/5b2/1q4k1/Q1q1k3/1B3Q2/3B2B1/3B4/b7 w - - 0 1",
    "8/2B1Q3/1B3B2/3b4/8/8/8/8 w - - 0 1",
    "5Q2/Q2b1b1b/1qQQ2Q1/4k3/2q2QQ1/1k2Q3/2Q3Q1/bQ2Q3 w - - 0 1",
    "8/2B1B3/1Q3B2/3b4/8/8/8/8 w - - 0 1",
    "8/4qb1Q/6k1/4Bq2/1B2B3/1k6/8/bQ5B w - - 0 1",
    "5Q2/3b4/1qQ5/4k3/2q2QQ1/1k2Q3/8/bQ6 w - - 0 1"
    };

    // 1 white figure
    char arr2[20][80] = {
    "8/8/8/8/8/8/8/5B2 w - - 0 1",
    "5bB1/8/8/8/8/8/8/8 w - - 0 1",
    "8/8/7B/8/8/8/8/8 w - - 0 1",
    "8/2b2k2/4b3/2qQ4/5b2/8/8/8 w - - 0 1",
    "8/2b2k2/4b3/2q2K2/5b2/8/8/8 w - - 0 1",
    "8/2b2k2/B3b3/2q5/5b2/8/8/8 w - - 0 1",
    "8/8/8/8/8/2bk4/6b1/5B2 w - - 0 1",
    "8/b1b2b2/8/4b3/8/2bk4/6b1/5B2 w - - 0 1",
    "8/b1b2b2/8/2Q1b3/8/2bk4/6b1/8 w - - 0 1",
    "7k/b1b2b2/3b4/b1q1b1b1/3K4/2bk4/6b1/8 w - - 0 1",
    "7k/b1b2b2/3b4/b1q1b1b1/2K5/2bk4/6b1/8 w - - 0 1",
    "8/b4b2/5K2/b5b1/4b3/2bk3k/6b1/8 w - - 0 1",
    "8/b4b2/8/b5b1/4b3/2bk3k/6b1/4Q3 w - - 0 1",
    "8/b4b2/8/b5b1/4bB2/2bk3k/6b1/8 w - - 0 1",
    "8/b4b2/3B4/b5b1/4b3/2bk3k/6b1/8 w - - 0 1",
    "8/b2K1b2/8/b5b1/4b3/2bk3k/6b1/8 w - - 0 1",
    "7Q/b4b2/8/b5b1/4b3/2bk3k/6b1/8 w - - 0 1",
    "1b1bb3/b2Q1b2/4b1k1/b2k4/8/8/8/8 w - - 0 1",
    "1b1bb3/b4b2/4b1k1/b2k4/8/8/8/6K1 w - - 0 1",
    "1b1bb3/b4b2/K3b1k1/b2k4/8/8/8/8 w - - 0 1"

    };

    // 12 white figures
    char arr3[20][80] = {
            "1b1bb3/b1Q2b2/K1B1b1kQ/b2k4/2B2B2/3K2Q1/1BBBQ3/8 w - - 0 1",
            "1bbbbbb1/1bbbbbb1/8/8/8/8/1BBBBBB1/1BBBBBB1 w - - 0 1",
            "2b1b1b1/2b2bb1/bB1B4/2bB1bB1/B1b5/2B1Bb2/4B3/1B1BBB2 w - - 0 1",
            "2b1b1b1/2b1Bbb1/bB1B1K1B/2bBBb2/B1b5/2Q1Bb2/4B3/4B3 w - - 0 1",
            "2bBb1b1/1BbBBbb1/bBQBQK2/1BbBBb2/2b5/5b2/8/8 w - - 0 1",
            "2bBb2B/2bB2b1/b1QK2B1/2bBbb2/2bB4/3B1b2/b2B4/3Q3B w - - 0 1",
            "1K1Bb2B/2bB2b1/b5B1/B1b2b2/2bB4/1b3bB1/b2B1Q2/3Q1b1B w - - 0 1",
            "1KB1b2B/2b3b1/b1Q2K2/2b2b2/B1bB1B1B/1b2B3/b1B3b1/3Q1b2 w - - 0 1",
            "1KB1b2B/1BbQBBb1/b1QBBKB1/2bbbb2/8/8/b5b1/5b2 w - - 0 1",
            "1KB4B/1B1QBBb1/2Q1BKB1/b1b1bb2/1k6/2Bq3b/bb6/5b2 w - - 0 1",
            "2B5/1B2BBb1/2Q3Q1/b1bqbb2/1k1KK1b1/2Qq4/b1BBB3/5b2 w - - 0 1",
            "8/K3B3/2Q2Q2/b2B1b2/1kBbQqB1/2bqbb2/b1BBBK2/5b2 w - - 0 1",
            "3Q3B/K1q4B/Q3k3/3B1b1b/1kBQ1q2/2b1bb2/b1BB4/B4b1K w - - 0 1",
            "Q6B/K1q4B/Q4B2/7b/b5k1/2bqbbB1/b1BBk3/B1Q2b1K w - - 0 1",
            "Q6B/2q2K1B/5B1b/1b3B1b/b3B1k1/2bq1QB1/b3k1b1/B1Q4K w - - 0 1",
            "Q1B5/5K2/3k1B1b/1b1B1B1b/b3B1kQ/2bq1QB1/b2Kk1b1/B7 w - - 0 1",
            "Q1B5/1Q3B2/3kbB1b/3B1B1b/4B1k1/2bq1Qb1/b2Kk1b1/B3Q3 w - - 0 1",
            "Q1B4B/1Q3B2/2Bkb2b/B3B2b/6k1/B1bq1Qb1/b2Kk1b1/4Q3 w - - 0 1",
            "Q1BKB2B/1Q3Bb1/2Bkb1Q1/B4Q2/2b5/B1bq2b1/b3k1bk/8 w - - 0 1",
            "Q1BKB2B/1Q3Bb1/2B1b1Q1/B4Qbk/7B/2bq4/b1bk3k/4b3 w - - 0 1"
    };



    struct timespec t0, t1, sum;
    unsigned int i;
    unsigned int j;
    uint64_t totaltimesec = 0;
    uint64_t  totaltimemicrosec = 0;


    long long avgtime = 0;

    for(i=0;i<20;i++){
        unsigned long long int *board = parseFEN(arr1[i]);
        clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
        for(j=0;j<100;j++) {
            calcmovesboard(board[0], board[1], board[2], board[3], board[4], board[5], 0);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);

        printf("\nDid %u calls in %.2g seconds", j, t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_nsec - t0.tv_nsec) / 1000);



    }

    //avgtime = totaltime;



}



int main(void){




    unsigned long long ***cmoves0 = ctmatrix("8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/5B2 w - - 0 1","8/8/8/8/8/8/6B1/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves0,calcmovesboard(2,0,0,0,0,0,0),0,"CMoves 0");

    // test for upper right corner sw & left diagonal capture sw
    unsigned long long int *pboard1 = parseFEN("5b2/6B1/8/8/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves1 = ctmatrix("5b2/7B/8/8/8/8/8/8 w - - 0 1","5b2/5B2/8/8/8/8/8/8 w - - 0 1","5bB1/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","5B2/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves1,calcmovesboard(pboard1[0],pboard1[1],pboard1[2],pboard1[3],pboard1[4],pboard1[5],0),0,"CMoves 1");

    // test right border move sw
    unsigned long long int *pboard2 = parseFEN("8/8/8/7B/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves2 = ctmatrix("8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/6B1/8/8/8/8 w - - 0 1","8/8/7B/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves2,calcmovesboard(pboard2[0],pboard2[1],pboard2[2],pboard2[3],pboard2[4],pboard2[5],0),0,"CMoves 2");

    // test left border move sw
    unsigned long long int *pboard3 = parseFEN("8/8/8/8/B7/8/8/8 w - - 0 1");
    unsigned long long ***cmoves3 = ctmatrix("8/8/8/8/1B6/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/B7/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves3,calcmovesboard(pboard3[0],pboard3[1],pboard3[2],pboard3[3],pboard3[4],pboard3[5],0),0,"CMoves 3");

    // test top border move sw
    unsigned long long int *pboard4 = parseFEN("3B4/8/8/8/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves4 = ctmatrix("4B3/8/8/8/8/8/8/8 w - - 0 1","2B5/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves4,calcmovesboard(pboard4[0],pboard4[1],pboard4[2],pboard4[3],pboard4[4],pboard4[5],0),0,"CMoves 4");

    // test climb left, climb right, climb top, capture right, capture left sw
    unsigned long long int *pboard5 = parseFEN("8/8/8/8/3bBb2/3BBB2/8/8 w - - 0 1");
    unsigned long long ***cmoves5 = ctmatrix("8/8/8/8/3bBb2/3B1Q2/8/8 w - - 0 1","8/8/8/8/3bBb2/3Q1B2/8/8 w - - 0 1","8/8/8/8/3bQb2/3B1B2/8/8 w - - 0 1","8/8/8/8/3bBB2/3B1B2/8/8 w - - 0 1","8/8/8/8/3BBb2/3B1B2/8/8 w - - 0 1",1);
    test(cmoves5,calcmovesboard(pboard5[0],pboard5[1],pboard5[2],pboard5[3],pboard5[4],pboard5[5],0),1,"CMoves 5");

    // test top left corner move dw
    unsigned long long int *pboard6 = parseFEN("2b5/3B4/1Q6/8/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves6 = ctmatrix("2b5/3Q4/1B6/8/8/8/8/8 w - - 0 1","2B5/3B4/1B6/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",1);
    test(cmoves6,calcmovesboard(pboard6[0],pboard6[1],pboard6[2],pboard6[3],pboard6[4],pboard6[5],0),1,"CMoves 6");

    // test climb from all directions on sw for mw
    unsigned long long int *pboard7 = parseFEN("8/2B1B3/1B3B2/3K4/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves7 = ctmatrix("8/2B1B3/1B3Q2/3b4/8/8/8/8 w - - 0 1","8/2B1Q3/1B3B2/3b4/8/8/8/8 w - - 0 1","8/2Q1B3/1B3B2/3b4/8/8/8/8 w - - 0 1","8/2B1B3/1Q3B2/3b4/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",4);
    test(cmoves7,calcmovesboard(pboard7[0],pboard7[1],pboard7[2],pboard7[3],pboard7[4],pboard7[5],0),4,"CMoves 7");

    // test capture sb from all directions for mw
    unsigned long long int *pboard8 = parseFEN("8/2b1b3/1b3b2/3K4/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves8 = ctmatrix("8/2b1b3/1b3B2/3b4/8/8/8/8 w - - 0 1","8/2b1B3/1b3b2/3b4/8/8/8/8 w - - 0 1","8/2B1b3/1b3b2/3b4/8/8/8/8 w - - 0 1","8/2b1b3/1B3b2/3b4/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves8,calcmovesboard(pboard8[0],pboard8[1],pboard8[2],pboard8[3],pboard8[4],pboard8[5],0),0,"CMoves 8");

    // test capture top of db from all directions for mw
    unsigned long long int *pboard9 = parseFEN("8/2q1q3/1q3q2/3K4/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves9 = ctmatrix("8/2q1q3/1q3K2/3b4/8/8/8/8 w - - 0 1","8/2q1K3/1q3q2/3b4/8/8/8/8 w - - 0 1","8/2K1q3/1q3q2/3b4/8/8/8/8 w - - 0 1","8/2q1q3/1K3q2/3b4/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves9,calcmovesboard(pboard9[0],pboard9[1],pboard9[2],pboard9[3],pboard9[4],pboard9[5],0),0,"CMoves 9");

    // test capture top of mb from all directions for mw
    unsigned long long int *pboard10 = parseFEN("8/2k1k3/1k3k2/3K4/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves10 = ctmatrix("8/2k1k3/1k3Q2/3b4/8/8/8/8 w - - 0 1","8/2k1Q3/1k3k2/3b4/8/8/8/8 w - - 0 1","8/2Q1k3/1k3k2/3b4/8/8/8/8 w - - 0 1","8/2k1k3/1Q3k2/3b4/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves10,calcmovesboard(pboard10[0],pboard10[1],pboard10[2],pboard10[3],pboard10[4],pboard10[5],0),0,"CMoves 10");

    // test free moves in all directions for db
    unsigned long long int *pboard11 = parseFEN("8/8/3q4/8/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves11 = ctmatrix("8/8/3b4/1b6/8/8/8/8 w - - 0 1","8/8/3b4/8/2b5/8/8/8 w - - 0 1","8/8/3b4/8/4b3/8/8/8 w - - 0 1","8/8/3b4/5b2/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves11,calcmovesboard(pboard11[0],pboard11[1],pboard11[2],pboard11[3],pboard11[4],pboard11[5],1),0,"CMoves 11");

    // test free moves in all directions for sb
    unsigned long long int *pboard12 = parseFEN("8/8/2b5/8/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves12 = ctmatrix("8/8/3b4/8/8/8/8/8 w - - 0 1","8/8/1b6/8/8/8/8/8 w - - 0 1","8/8/8/2b5/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves12,calcmovesboard(pboard12[0],pboard12[1],pboard12[2],pboard12[3],pboard12[4],pboard12[5],1),0,"CMoves 12");

    // test moves in all directions  surrounded by sw for sb
    unsigned long long int *pboard13 = parseFEN("8/8/1BbB4/1BBB4/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves13 = ctmatrix("8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/1B1B4/1bBB4/8/8/8/8 w - - 0 1","8/8/1B1B4/1BBb4/8/8/8/8 w - - 0 1",0);
    test(cmoves13,calcmovesboard(pboard13[0],pboard13[1],pboard13[2],pboard13[3],pboard13[4],pboard13[5],1),0,"CMoves 13");

    // test down left corner  capture sw right diagonal down for sb
    unsigned long long int *pboard14 = parseFEN("8/8/8/8/8/8/b7/1B6 b - - 0 1");
    unsigned long long ***cmoves14 = ctmatrix("8/8/8/8/8/8/1b6/1B6 b - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/1b6 b - - 0 1",0);
    test(cmoves14,calcmovesboard(pboard14[0],pboard14[1],pboard14[2],pboard14[3],pboard14[4],pboard14[5],1),0,"CMoves 14");

    // test starting board for sw pos b2
    unsigned long long int *pboard15 = parseFEN("1bbbbbb1/1bbbbbb1/8/8/8/8/1BBBBBB1/1BBBBBB1 w - - 0 1");
    unsigned long long ***cmoves15 = ctmatrix("1bbbbbb1/1bbbbbb1/8/8/8/8/2QBBBB1/1BBBBBB1 w - - 0 1","1bbbbbb1/1bbbbbb1/8/8/8/8/B1BBBBB1/1BBBBBB1 w - - 0 1","1bbbbbb1/1bbbbbb1/8/8/8/1B6/2BBBBB1/1BBBBBB1 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",11);
    test(cmoves15,calcmovesboard(pboard15[0],pboard15[1],pboard15[2],pboard15[3],pboard15[4],pboard15[5],0),11,"CMoves 15");

    // test starting board for sb pos g7
    unsigned long long int *pboard16 = parseFEN("1bbbbbb1/1bbbbbb1/8/8/8/8/1BBBBBB1/1BBBBBB1 w - - 0 1");
    unsigned long long ***cmoves16 = ctmatrix("1bbbbbb1/1bbbbb1b/8/8/8/8/1BBBBBB1/1BBBBBB1 w - - 0 1","1bbbbbb1/1bbbbq2/8/8/8/8/1BBBBBB1/1BBBBBB1 w - - 0 1","1bbbbbb1/1bbbbb2/6b1/8/8/8/1BBBBBB1/1BBBBBB1 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",0);
    test(cmoves16,calcmovesboard(pboard16[0],pboard16[1],pboard16[2],pboard16[3],pboard16[4],pboard16[5],1),0,"CMoves 16");

    // test starting board for sb pos b8
    unsigned long long int *pboard17 = parseFEN("1bbbbbb1/1bbbbbb1/8/8/8/8/1BBBBBB1/1BBBBBB1 w - - 0 1");
    unsigned long long ***cmoves17 = ctmatrix("2qbbbb1/1bbbbbb1/8/8/8/8/1BBBBBB1/1BBBBBB1 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","2bbbbb1/1qbbbbb1/8/8/8/8/1BBBBBB1/1BBBBBB1 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",11);
    test(cmoves17,calcmovesboard(pboard17[0],pboard17[1],pboard17[2],pboard17[3],pboard17[4],pboard17[5],1),11,"CMoves 17");

    // test starting board without g1 for sw pos a2
    unsigned long long int *pboard18 = parseFEN("1bbbbbb1/1bbbbb2/8/8/8/8/1BBBBBB1/1BBBBB2 w - - 0 1");
    unsigned long long ***cmoves18 = ctmatrix("1bbbbbb1/1bbbbb2/8/8/8/8/2QBBBB1/1BBBBB2 w - - 0 1","1bbbbbb1/1bbbbb2/8/8/8/8/B1BBBBB1/1BBBBB2 w - - 0 1","1bbbbbb1/1bbbbb2/8/8/8/1B6/2BBBBB1/1BBBBB2 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",10);
    test(cmoves18,calcmovesboard(pboard18[0],pboard18[1],pboard18[2],pboard18[3],pboard18[4],pboard18[5],0),10,"CMoves 18");

    // test moves variation for dw
    unsigned long long int *pboard19 = parseFEN("8/4q1b1/3B4/5K2/1k1b4/B7/2Q1bB2/4bB2 w - - 0 1");
    unsigned long long ***cmoves19 = ctmatrix("8/4q1b1/3B4/5K2/1k1b4/B3B3/2B1bB2/4bB2 w - - 0 1","8/4q1b1/3B4/5K2/1k1B4/B7/2B1bB2/4bB2 w - - 0 1","8/4q1b1/3B4/5K2/1Q1b4/B7/2B1bB2/4bB2 w - - 0 1","8/4q1b1/3B4/5K2/1k1b4/Q7/2B1bB2/4bB2 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",4);
    test(cmoves19,calcmovesboard(pboard19[0],pboard19[1],pboard19[2],pboard19[3],pboard19[4],pboard19[5],0),4,"CMoves 19");

    // test moves variation for mw
    unsigned long long int *pboard20 = parseFEN("8/4q1b1/3B4/5K2/1k1b4/B7/2Q1bB2/4bB2 w - - 0 1");
    unsigned long long ***cmoves20 = ctmatrix("8/4q1b1/3B3B/5b2/1k1b4/B7/2Q1bB2/4bB2 w - - 0 1","8/4q1B1/3B4/5b2/1k1b4/B7/2Q1bB2/4bB2 w - - 0 1","8/4K1b1/3B4/5b2/1k1b4/B7/2Q1bB2/4bB2 w - - 0 1","8/4q1b1/3Q4/5b2/1k1b4/B7/2Q1bB2/4bB2 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",5);
    test(cmoves20,calcmovesboard(pboard20[0],pboard20[1],pboard20[2],pboard20[3],pboard20[4],pboard20[5],0),5,"CMoves 20");

    // test moves variation for db
    unsigned long long int *pboard21 = parseFEN("2bB4/2bB1q2/7B/4b1K1/2k5/4b3/1B1Q4/8 w - - 0 1");
    unsigned long long ***cmoves21 = ctmatrix("2bB4/2bB1b2/3b3B/4b1K1/2k5/4b3/1B1Q4/8 w - - 0 1","2bB4/2bB1b2/7B/4q1K1/2k5/4b3/1B1Q4/8 w - - 0 1","2bB4/2bB1b2/7B/4b1q1/2k5/4b3/1B1Q4/8 w - - 0 1","2bB4/2bB1b2/7b/4b1K1/2k5/4b3/1B1Q4/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",4);
    test(cmoves21,calcmovesboard(pboard21[0],pboard21[1],pboard21[2],pboard21[3],pboard21[4],pboard21[5],1),4,"CMoves 21");

    // test moves variation for mb
    unsigned long long int *pboard22 = parseFEN("2bB4/2bB1q2/7B/4b1K1/2k5/4b3/1B1Q4/8 w - - 0 1");
    unsigned long long ***cmoves22 = ctmatrix("2bB4/2bB1q2/7B/4b1K1/2B5/b3b3/1B1Q4/8 w - - 0 1","2bB4/2bB1q2/7B/4b1K1/2B5/4b3/1b1Q4/8 w - - 0 1","2bB4/2bB1q2/7B/4b1K1/2B5/4b3/1B1k4/8 w - - 0 1","2bB4/2bB1q2/7B/4b1K1/2B5/4q3/1B1Q4/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1",5);
    test(cmoves22,calcmovesboard(pboard22[0],pboard22[1],pboard22[2],pboard22[3],pboard22[4],pboard22[5],1),5,"CMoves 22");

    // test moves variation for sb
    unsigned long long int *pboard23 = parseFEN("2bB4/2bB1q2/7B/4b1K1/2k5/4b3/1B1Q4/8 w - - 0 1");
    unsigned long long ***cmoves23 = ctmatrix("8/8/8/8/8/8/8/8 w - - 0 1","1b1B4/2bB1q2/7B/4b1K1/2k5/4b3/1B1Q4/8 w - - 0 1","3B4/2qB1q2/7B/4b1K1/2k5/4b3/1B1Q4/8 w - - 0 1","8/8/8/8/8/8/8/8 w - - 0 1","3B4/2bb1q2/7B/4b1K1/2k5/4b3/1B1Q4/8 w - - 0 1",3);
    test(cmoves23,calcmovesboard(pboard23[0],pboard23[1],pboard23[2],pboard23[3],pboard23[4],pboard23[5],1),3,"CMoves 23");

    // test moves variation for sb
    unsigned long long int *pboard24 = parseFEN("2bB4/2bB1q2/7B/4b1K1/2k5/4b3/1B1Q4/8 b - - 0 1");
    unsigned long long ***cmoves24 = ctmatrix("8/8/8/8/8/8/8/8 b - - 0 1","2bB4/1b1B1q2/7B/4b1K1/2k5/4b3/1B1Q4/8 b - - 0 1","2bB4/3B1q2/2b4B/4b1K1/2k5/4b3/1B1Q4/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1",2);
    test(cmoves24,calcmovesboard(pboard24[0],pboard24[1],pboard24[2],pboard24[3],pboard24[4],pboard24[5],1),2,"CMoves 24");

    // test far right out of bounds db
    unsigned long long int *pboard25 = parseFEN("8/1qqqqqq1/8/8/8/2B5/2QQQQQ1/1Q6 b - - 0 1");
    unsigned long long ***cmoves25 = ctmatrix("8/1qqqqqb1/4b3/8/8/2B5/2QQQQQ1/1Q6 b - - 0 1","8/1qqqqqb1/8/5b2/8/2B5/2QQQQQ1/1Q6 b - - 0 1","8/1qqqqqb1/8/7b/8/2B5/2QQQQQ1/1Q6 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1",0);
    test(cmoves25,calcmovesboard(pboard25[0],pboard25[1],pboard25[2],pboard25[3],pboard25[4],pboard25[5],1),0,"CMoves 25");

    // test center & far right (at down right corner) out of bounds db
    unsigned long long int *pboard26 = parseFEN("8/8/8/8/8/8/5q2/8 b - - 0 1");
    unsigned long long ***cmoves26 = ctmatrix("8/8/8/8/8/8/5b2/3b4 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1",0);
    test(cmoves26,calcmovesboard(pboard26[0],pboard26[1],pboard26[2],pboard26[3],pboard26[4],pboard26[5],1),0,"CMoves 26");

    // test center & far left (at down left corner) out of bounds db
    unsigned long long int *pboard27 = parseFEN("8/8/8/8/8/8/2q5/8 b - - 0 1");
    unsigned long long ***cmoves27 = ctmatrix("8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/2b5/4b3 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1",0);
    test(cmoves27,calcmovesboard(pboard27[0],pboard27[1],pboard27[2],pboard27[3],pboard27[4],pboard27[5],1),0,"CMoves 27");

    // test center out of bounds db
    unsigned long long int *pboard28 = parseFEN("8/8/8/8/8/8/4q3/8 b - - 0 1");
    unsigned long long ***cmoves28 = ctmatrix("8/8/8/8/8/8/4b3/2b5 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/4b3/6b1 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1",0);
    test(cmoves28,calcmovesboard(pboard28[0],pboard28[1],pboard28[2],pboard28[3],pboard28[4],pboard28[5],1),0,"CMoves 28");

    // test center & far right (at top right corner) out of bounds dw
    unsigned long long int *pboard29 = parseFEN("8/5Q2/8/8/8/8/8/8 b - - 0 1");
    unsigned long long ***cmoves29 = ctmatrix("8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","3B4/5B2/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1",0);
    test(cmoves29,calcmovesboard(pboard29[0],pboard29[1],pboard29[2],pboard29[3],pboard29[4],pboard29[5],0),0,"CMoves 29");

    // test center & far left (at top left corner) out of bounds dw
    unsigned long long int *pboard30 = parseFEN("8/2Q5/8/8/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves30 = ctmatrix("4B3/2B5/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1",0);
    test(cmoves30,calcmovesboard(pboard30[0],pboard30[1],pboard30[2],pboard30[3],pboard30[4],pboard30[5],0),0,"CMoves 30");

    // test center & far left (at top left corner) out of bounds dw
    unsigned long long int *pboard31 = parseFEN("8/4Q3/8/8/8/8/8/8 w - - 0 1");
    unsigned long long ***cmoves31 = ctmatrix("6B1/4B3/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1","2B5/4B3/8/8/8/8/8/8 w - - 0 1","8/8/8/8/8/8/8/8 b - - 0 1",0);
    test(cmoves31,calcmovesboard(pboard31[0],pboard31[1],pboard31[2],pboard31[3],pboard31[4],pboard31[5],0),0,"CMoves 31");



/*
    unsigned long long int ***moves = calcmovesboard(pboard26[0],pboard26[1],pboard26[2],pboard26[3],pboard26[4],pboard26[5],1);

    int countf = 1;


    for(int c = 0;c<12 ;c++){
        printf(" ----------- %d ----------- \n",countf);
        for(int d = 0;d<5;d++){

            for(int e = 0; e<6; e++){
                char figtype[3];

                if(e==0){
                    figtype[0] = 'S';
                    figtype[1] = 'W';
                }
                if(e==1){
                    figtype[0] = 'S';
                    figtype[1] = 'B';
                }
                if(e==2){
                    figtype[0] = 'D';
                    figtype[1] = 'W';
                }
                if(e==3){
                    figtype[0] = 'D';
                    figtype[1] = 'B';
                }
                if(e==4){
                    figtype[0] = 'M';
                    figtype[1] = 'W';
                }
                if(e==5){
                    figtype[0] = 'M';
                    figtype[1] = 'B';
                }

                printf("%s: %llu \n",figtype,moves[c][d][e]);
            }
            printf(" -------------------------- \n");

        }
        countf++;
    }

*/


}
