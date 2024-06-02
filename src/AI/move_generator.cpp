//
// Created by limin on 5/22/20.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "move_generator.h"
#include "eval.h"


unsigned long long int ***calcmovesboard(unsigned long long int sw, unsigned long long int sb, unsigned long long int dw, unsigned long long int db, unsigned long long int mw, unsigned long long int mb, int player){

    // 1. SW 1. Right Move
    //       2. Left Move
    //       3. Up Move
    //       4. Right Capture
    //       5. Left Capture
    // 2. SB 1. Right Move
    //       2. Left Move
    //       3. Down Move
    //       4. Left Capture
    //       5. Right Capture
    // 3. DW 1. Lower Left Move/Capture
    //       2. Upper Left Move/Capture
    //       3. Upper Right Move/Capture
    //       4. Lower Right Move/Capture
    // 4. DB 1. Lower Right Move/Capture
    //       2. Upper Right Move/Capture
    //       3. Upper Left Move/Capture
    //       4. Lower Left Move/Capture
    // 5. MW 1. Lower Left Move/Capture
    //       2. Upper Left Move/Capture
    //       3. Upper Right Move/Capture
    //       4. Lower Right Move/Capture
    // 6. MB 1. Lower Right Move/Capture
    //       2. Upper Right Move/Capture
    //       3. Upper Left Move/Capture
    //       4. Lower Left Move/Capture
    unsigned long long int figposarr[6][12] = {0};
    int figposarrlen[6];

    unsigned long long int posarr1[6] = {sw,sb,dw,db,mw,mb};
    int countbinpos;
    int countindivfigs;
    for(int i=0; i<6; i++){
        countbinpos = 0;
        countindivfigs = 0;
        figposarrlen[i] = 0;
        unsigned long long int indivfigs[12];
        memset(indivfigs,0,sizeof(indivfigs));
        // while posarr is greater than 0
        while(posarr1[i]){
            // omit corner board positions
            if(!(countbinpos == 0 || countbinpos == 7 || countbinpos == 56 || countbinpos == 63)) {
                if (posarr1[i] & 1) {
                    indivfigs[countindivfigs] = (unsigned long long int) pow(2, countbinpos);
                    countindivfigs++;
                    figposarrlen[i] = countindivfigs;
                }
            }
            countbinpos++;
            posarr1[i] = posarr1[i] >> 1;
        }

        for(int c = 0;c<countindivfigs;c++){
            figposarr[i][c] = indivfigs[c];

        }

    }
    unsigned long long int posarr[6] = {sw,sb,dw,db,mw,mb};
    unsigned long long int occupied = sw | sb | dw | db | mw | mb;


    unsigned long long int ***moves;
    moves = calloc(12,sizeof(unsigned long long int**));

    for(int i=0;i<12;i++){
        moves[i] = calloc(5,sizeof(unsigned long long int*));
        for(int j=0;j<5;j++){
            moves[i][j] = calloc(6,sizeof(unsigned long long int));
        }
    }

    int poscount = 0;
    numMoves = 0;
    for(int i=0;i<6;i++){

        // white == '0'
        // skip these figures if blacks's turn (assumed to be minimizer)
        if(player == 0 && (i == 1 || i == 3 || i == 5)){
            continue;
        }
        // black == '1'
        // skip these figures if white's turn (assumed to be optimizer)
        if(player == 1 && (i == 0 || i == 2 || i == 4)){
            continue;
        }


        for(int j=0;j < figposarrlen[i] ;j++){
            //printf("%d \n",j);

            int posexp = (int) log2(figposarr[i][j]);
            unsigned  long long int pos = figposarr[i][j];
            unsigned long long int figpos[5];
            memset(figpos,0,sizeof(figpos));
            //printf("Posexp: %d \n",posexp);
            unsigned long long int movepos = 0;
            unsigned long long int nmoves[5][6] = {0};

            for(int k=0;k<5;k++){

                if(i < 2 || k != 4){
                    nmoves[k][0] = sw;
                    nmoves[k][1] = sb;
                    nmoves[k][2] = dw;
                    nmoves[k][3] = db;
                    nmoves[k][4] = mw;
                    nmoves[k][5] = mb;
                }
                else {
                    nmoves[k][0] = 0;
                    nmoves[k][1] = 0;
                    nmoves[k][2] = 0;
                    nmoves[k][3] = 0;
                    nmoves[k][4] = 0;
                    nmoves[k][5] = 0;
                }

            }

            if(posexp == 0 || posexp == 7 || posexp == 56 || posexp == 63){
                break;
            }

            if(i == 0){
                int tookmove = 0;

                if(!(posexp == 0 || posexp == 7 || posexp == 56 || posexp == 63)) {

                    tookmove = 0;
                    // check right move
                    if(!(posexp == 1 || posexp == 8 || posexp == 16 || posexp == 24 || posexp == 32 || posexp == 40 || posexp == 48 || posexp == 57)) {
                        if(!((pos >> 1) & (occupied &~ sw))) {
                            figpos[0] = pos >> 1;
                            movepos = pos >> 1;

                            // remove fig from sw add to dw
                            if(movepos & sw){
                                nmoves[0][0] = sw &~ pos &~ movepos;
                                nmoves[0][2] = dw | movepos;
                                tookmove = 1;
                            }
                            // remove fig from old pos in sw to new pos
                            if(!(movepos & occupied)){
                                nmoves[0][0] = (sw | movepos) &~ pos;
                                tookmove = 1;
                            }
                        }
                    }
                    if(tookmove == 0){
                        nmoves[0][0] = 0;
                        nmoves[0][1] = 0;
                        nmoves[0][2] = 0;
                        nmoves[0][3] = 0;
                        nmoves[0][4] = 0;
                        nmoves[0][5] = 0;
                    }

                    tookmove = 0;
                    // check left move
                    if(!(posexp == 6 || posexp == 15 || posexp == 23 || posexp == 31 || posexp == 39 || posexp == 47 || posexp == 55 || posexp == 62)) {

                        if (!((pos << 1) & (occupied &~ sw))) {
                            figpos[1] = pos << 1;
                            movepos =  pos << 1;

                            // remove fig from sw add to dw
                            if(movepos & sw){
                                nmoves[1][0] = sw &~ pos &~ movepos;
                                nmoves[1][2] = dw | movepos;
                                tookmove = 1;
                            }
                            // move fig from old pos to new pos in sw
                            if(!(movepos & occupied)){
                                nmoves[1][0] = (sw | movepos) &~ pos;
                                tookmove = 1;
                            }
                        }
                    }
                    if(tookmove == 0){
                        nmoves[1][0] = 0;
                        nmoves[1][1] = 0;
                        nmoves[1][2] = 0;
                        nmoves[1][3] = 0;
                        nmoves[1][4] = 0;
                        nmoves[1][5] = 0;
                    }

                    tookmove = 0;
                        // check for top row
                    if (!(posexp == 57 || posexp == 58 || posexp == 59 || posexp == 60 || posexp == 61 ||
                          posexp == 62)) {
                        int tookmove2 = 0;

                        // add up move
                        if (!(posexp == 48 || posexp == 55) &
                            !((pos << 8) & (occupied &~ sw))) {
                            figpos[2] = pos << 8;
                            movepos = pos << 8;

                            // remove fig from sw add to dw
                            if(movepos & sw){
                                nmoves[2][0] = sw &~ pos &~ movepos;
                                nmoves[2][2] = dw | movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                            // move fig from old pos to new pos in sw
                            if(!(movepos & occupied)){
                                nmoves[2][0] = (sw | movepos) &~ pos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                        }
                        if(tookmove2 == 0){
                            nmoves[2][0] = 0;
                            nmoves[2][1] = 0;
                            nmoves[2][2] = 0;
                            nmoves[2][3] = 0;
                            nmoves[2][4] = 0;
                            nmoves[2][5] = 0;
                        }

                        tookmove2 = 0;
                        // conquer right diag up
                        if (!(posexp == 8 || posexp == 16 || posexp == 24 ||
                              posexp == 32 || posexp == 40 || posexp == 48 || posexp == 49) &&
                            ((pos << 7 & sb) || (pos << 7 & db) || (pos << 7 & mb))) {
                            figpos[3] = pos << 7;
                            movepos = pos << 7;

                            // move fig from old pos to new pos remove captured sb
                            if(movepos & sb){
                                nmoves[3][0] = (sw | movepos) &~ pos;
                                nmoves[3][1] = sb &~ movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                            // capture db and turn to mw
                            if(movepos & db){
                                nmoves[3][0] = sw &~ pos;
                                nmoves[3][3] = db &~ movepos;
                                nmoves[3][4] = mw | movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                            // capture mb and turn to dw
                            if(movepos & db){
                                nmoves[3][0] = sw &~ pos;
                                nmoves[3][5] = mb &~ movepos;
                                nmoves[3][3] = dw | movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                        }
                        if(tookmove2 == 0){
                            nmoves[3][0] = 0;
                            nmoves[3][1] = 0;
                            nmoves[3][2] = 0;
                            nmoves[3][3] = 0;
                            nmoves[3][4] = 0;
                            nmoves[3][5] = 0;
                        }

                        tookmove2 = 0;
                        // conquer left diag up
                        if (!(posexp == 15 || posexp == 23 || posexp == 31 ||
                              posexp == 39 || posexp == 47 || posexp == 54 || posexp == 55) &&
                            ((pos << 9 & sb) || (pos << 9 & db) || (pos << 9 & mb))) {
                            figpos[4] = pos << 9;
                            movepos = pos << 9;

                            // move fig from old pos to new pos remove captured sb
                            if(movepos & sb){
                                nmoves[4][0] = (sw | movepos) &~ pos;
                                nmoves[4][1] = sb &~ movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                            // capture db and turn to mw
                            if(movepos & db){
                                nmoves[4][0] = sw &~ pos;
                                nmoves[4][3] = db &~ movepos;
                                nmoves[4][4] = mw | movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                            // capture mb and turn to dw
                            if(movepos & mb){
                                nmoves[4][0] = sw &~ pos;
                                nmoves[4][5] = mb &~ movepos;
                                nmoves[4][2] = dw | movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }

                        }
                        if(tookmove2 == 0){
                            nmoves[4][0] = 0;
                            nmoves[4][1] = 0;
                            nmoves[4][2] = 0;
                            nmoves[4][3] = 0;
                            nmoves[4][4] = 0;
                            nmoves[4][5] = 0;
                        }
                    }
                    if(tookmove == 0){
                        for(int s = 2; s<5;s++){
                            nmoves[s][0] = 0;
                            nmoves[s][1] = 0;
                            nmoves[s][2] = 0;
                            nmoves[s][3] = 0;
                            nmoves[s][4] = 0;
                            nmoves[s][5] = 0;
                        }
                    }
                }
            }


            if(i == 1){
                int tookmove = 0;

                // add down move
                // check if position is free or occupied by single of same color
                if(!(posexp == 0 || posexp == 7 || posexp == 56 || posexp == 63)) {
                    // check right move
                    if(!(posexp == 1 || posexp == 8 || posexp == 16 || posexp == 24 || posexp == 32 || posexp == 40 || posexp == 48 || posexp == 57)) {
                        if(!((pos >> 1) & (occupied &~ sb))) {
                            figpos[0] = pos >> 1;
                            movepos = pos >> 1;

                            // remove fig from sb add to db
                            if(movepos & sb){
                                nmoves[0][1] = sb &~ pos &~ movepos;
                                nmoves[0][3] = db | movepos;
                                tookmove = 1;
                            }

                            // remove fig from old pos in sb to new pos
                            if(!(movepos & occupied)){
                                nmoves[0][1] = (sb | movepos) &~ pos;
                                tookmove = 1;
                            }

                        }
                    }
                    if(tookmove == 0){
                        nmoves[0][0] = 0;
                        nmoves[0][1] = 0;
                        nmoves[0][2] = 0;
                        nmoves[0][3] = 0;
                        nmoves[0][4] = 0;
                        nmoves[0][5] = 0;
                    }

                    tookmove = 0;
                    // check left move
                    if(!(posexp == 6 || posexp == 15 || posexp == 23 || posexp == 31 || posexp == 39 || posexp == 47 || posexp == 55 || posexp == 62)) {

                        if (!((pos << 1) & (occupied &~ sb))) {
                            figpos[1]  = pos << 1;
                            movepos = pos << 1;

                            // remove fig from sb add to db
                            if(movepos & sb){
                                nmoves[1][1] = sb &~ pos &~ movepos;
                                nmoves[1][3] = db | movepos;
                                tookmove = 1;
                            }

                            // remove fig from old pos in sb to new pos
                            if(!(movepos & occupied)){
                                nmoves[1][1] = (sb | movepos) &~ pos;
                                tookmove = 1;
                            }
                        }
                    }
                    if(tookmove == 0){
                        nmoves[1][0] = 0;
                        nmoves[1][1] = 0;
                        nmoves[1][2] = 0;
                        nmoves[1][3] = 0;
                        nmoves[1][4] = 0;
                        nmoves[1][5] = 0;
                    }

                    tookmove = 0;
                    // check for bottom row
                    if (!(posexp == 1 || posexp == 2 || posexp == 3 || posexp == 4 || posexp == 5 ||
                          posexp == 6)) {
                        int tookmove2 = 0;

                        if (!(posexp == 8 || posexp == 15) &&
                            !((pos >> 8) & (occupied &~ sb))) {
                            figpos[2] = pos >> 8;
                            movepos = pos >> 8;
                            // remove fig from sb add to db
                            if(movepos & sb){
                                nmoves[2][1] = sb &~ pos &~ movepos;
                                nmoves[2][3] = db | movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }

                            // remove fig from old pos in sb to new pos
                            if(!(movepos & occupied)){
                                nmoves[2][1] = (sb | movepos) &~ pos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                        }
                        if(tookmove2 == 0){
                            nmoves[2][0] = 0;
                            nmoves[2][1] = 0;
                            nmoves[2][2] = 0;
                            nmoves[2][3] = 0;
                            nmoves[2][4] = 0;
                            nmoves[2][5] = 0;
                        }

                        tookmove2 = 0;
                        // conquer left diag down
                        if (!(posexp == 14 || posexp == 15 || posexp == 23 || posexp == 31 ||
                              posexp == 39 || posexp == 47 || posexp == 53) &&
                            ((pos >> 7 & sw) || (pos >> 7 & dw) || (pos >> 7 & mw))) {
                            figpos[3] = pos >> 7;
                            movepos = pos >> 7;

                            // move fig from old pos to new pos remove captured sw
                            if(movepos & sw){
                                nmoves[3][1] = (sb | movepos) &~ pos;
                                nmoves[3][0] = sw &~ movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                            // capture dw and turn to mb
                            if(movepos & dw){
                                nmoves[3][1] = sb &~ pos;
                                nmoves[3][4] = dw &~ movepos;
                                nmoves[3][5] = mb | movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                            // capture mw and turn to db
                            if(movepos & mw){
                                nmoves[3][1] = sb &~ pos;
                                nmoves[3][4] = mw &~ movepos;
                                nmoves[3][3] = db | movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                        }
                        if(tookmove2 == 0){
                            nmoves[3][0] = 0;
                            nmoves[3][1] = 0;
                            nmoves[3][2] = 0;
                            nmoves[3][3] = 0;
                            nmoves[3][4] = 0;
                            nmoves[3][5] = 0;
                        }

                        tookmove2 = 0;
                        // conquer right diag down
                        if (!(posexp == 8 || posexp == 9 || posexp == 16 || posexp == 24 ||
                              posexp == 32 || posexp == 40 || posexp == 48) &&
                            ((pos >> 9 & sw) || (pos >> 9 & dw) || (pos >> 9 & mw))) {
                            figpos[4] = pos >> 9;
                            movepos = pos >> 9;

                            // move fig from old pos to new pos remove captured sw
                            if(movepos & sw){
                                nmoves[4][1] = (sb | movepos) &~ pos;
                                nmoves[4][0] = sw &~ movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                            // capture dw and turn to mb
                            if(movepos & dw){
                                nmoves[4][1] = sb &~ pos;
                                nmoves[4][4] = dw &~ movepos;
                                nmoves[4][5] = mb | movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                            // capture mw and turn to db
                            if(movepos & mw){
                                nmoves[4][1] = sb &~ pos;
                                nmoves[4][4] = mw &~ movepos;
                                nmoves[4][3] = db | movepos;
                                tookmove = 1;
                                tookmove2 = 1;
                            }
                        }
                        if(tookmove2 == 0){
                            nmoves[4][0] = 0;
                            nmoves[4][1] = 0;
                            nmoves[4][2] = 0;
                            nmoves[4][3] = 0;
                            nmoves[4][4] = 0;
                            nmoves[4][5] = 0;
                        }

                    }
                    if(tookmove == 0){
                        for(int s = 2; s<5;s++){
                            nmoves[s][0] = 0;
                            nmoves[s][1] = 0;
                            nmoves[s][2] = 0;
                            nmoves[s][3] = 0;
                            nmoves[s][4] = 0;
                            nmoves[s][5] = 0;
                        }
                    }
                }
            }


            // dw & mw moves
            if(i == 2 || i == 4){
                int tookmove = 0;

                if(!(posexp == 0 || posexp == 7 || posexp == 56 || posexp == 63)) {
                    // check for bottom row
                    if (!(posexp == 57 || posexp == 58 || posexp == 59 || posexp == 60 || posexp == 61 || posexp == 62)) {

                        int tookmove2 = 0;
                        // lower right jump
                        if (!(posexp == 1 || posexp == 8 || posexp == 9 || posexp == 16 || posexp == 17 ||
                              posexp == 24 || posexp == 25 || posexp == 32 || posexp == 33 || posexp == 40 ||
                              posexp == 41 || posexp == 48 || posexp == 49 || posexp == 50)) {
                            if ((pos << 6 & sb) || (pos << 6 & db) || (pos << 6 & mb) || (pos << 6 & sw) ||
                                !(pos << 6 & occupied)) {
                                figpos[0] = pos << 6;
                                movepos = pos << 6;

                                // move dw/mw from old pos to new
                                if(!(movepos & occupied)){
                                    if(i==2){
                                        nmoves[0][2] = dw &~ pos;
                                        nmoves[0][0] = sw | movepos | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[0][4] = mw &~ pos;
                                        nmoves[0][0] = sw | movepos;
                                        nmoves[0][1] = sb | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on sw
                                if(movepos & sw){
                                    if(i==2){
                                        nmoves[0][0] = (sw | pos) &~ movepos;
                                        nmoves[0][2] = (dw | movepos) &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[0][0] = sw &~ movepos;
                                        nmoves[0][1] = sb | pos;
                                        nmoves[0][2] = dw | movepos;
                                        nmoves[0][4] = mw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // dw/mw capture sb
                                if(movepos & sb){
                                    if(i==2){
                                        nmoves[0][0] = sw | movepos | pos;
                                        nmoves[0][1] = sb &~ movepos;
                                        nmoves[0][2] = dw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                       nmoves[0][0] = sw | movepos;
                                       nmoves[0][1] = (sb | pos) &~ movepos;
                                       nmoves[0][4] = mw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on db
                                if(movepos & db){
                                    if(i==2){
                                        nmoves[0][2] = dw &~ pos;
                                        nmoves[0][0] = sw | pos;
                                        nmoves[0][3] = db &~ movepos;
                                        nmoves[0][4] = mw | movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                      nmoves[0][4] = (mw|movepos) &~ pos;
                                      nmoves[0][1] = sb | pos;
                                      nmoves[0][3] = db &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                if(movepos & mb){
                                    if(i==2){
                                        nmoves[0][2] = (dw|movepos) &~ pos;
                                        nmoves[0][0] = sw | pos;
                                        nmoves[0][5] = mb &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[0][2] = dw | movepos;
                                        nmoves[0][4] = mw &~ pos;
                                        nmoves[0][1] = sb | pos;
                                        nmoves[0][5] = mb &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }


                            }
                        }

                        if(tookmove2 == 0){
                            nmoves[0][0] = 0;
                            nmoves[0][1] = 0;
                            nmoves[0][2] = 0;
                            nmoves[0][3] = 0;
                            nmoves[0][4] = 0;
                            nmoves[0][5] = 0;
                        }

                        tookmove2 = 0;
                        // upper right jump
                        if (!(posexp == 8 || posexp == 16 || posexp == 24 || posexp == 32 || posexp == 40 ||
                              posexp == 41 || posexp == 48 || posexp == 49 || posexp == 50 || posexp == 51 ||
                              posexp == 52 || posexp == 53 || posexp == 54 || posexp == 55)) {
                            if ((pos << 15 & sb) || (pos << 15 & db) || (pos << 15 & mb) ||
                                (pos << 15 & sw) || !(pos << 15 & occupied)) {
                                figpos[1] = pos << 15;
                                movepos = pos << 15;

                                // move dw/mw from old pos to new
                                if(!(movepos & occupied)){
                                    if(i==2){
                                        nmoves[1][2] = dw &~ pos;
                                        nmoves[1][0] = sw | movepos | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[1][4] = mw &~ pos;
                                        nmoves[1][0] = sw | movepos;
                                        nmoves[1][1] = sb | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on sw
                                if(movepos & sw){
                                    if(i==2){
                                        nmoves[1][0] = (sw | pos) &~ movepos;
                                        nmoves[1][2] = (dw | movepos) &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[1][0] = sw &~ movepos;
                                        nmoves[1][1] = sb | pos;
                                        nmoves[1][2] = dw | movepos;
                                        nmoves[1][4] = mw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                //TODO this case with sb capture was missing! Check other move directions for other figures if this dir is missing for them as well!!
                                // dw & mw capture sb
                                if(movepos & sb){
                                    if(i==2){
                                        nmoves[1][0] = sw | movepos | pos;
                                        nmoves[1][1] = sb &~ movepos;
                                        nmoves[1][2] = dw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[1][0] = sw | movepos;
                                        nmoves[1][1] = (sb | pos) &~ movepos;
                                        nmoves[1][4] = mw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on db
                                if(movepos & db){
                                    if(i==2){
                                        nmoves[1][2] = dw &~ pos;
                                        nmoves[1][0] = sw | pos;
                                        nmoves[1][3] = db &~ movepos;
                                        nmoves[1][4] = mw | movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[1][4] = (mw|movepos) &~ pos;
                                        nmoves[1][1] = sb | pos;
                                        nmoves[1][3] = db &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                if(movepos & mb){
                                    if(i==2){
                                        nmoves[1][2] = (dw|movepos) &~ pos;
                                        nmoves[1][0] = sw | pos;
                                        nmoves[1][5] = mb &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[1][2] = dw | movepos;
                                        nmoves[1][4] = mw &~ pos;
                                        nmoves[1][1] = sb | pos;
                                        nmoves[1][5] = mb &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }
                            }
                        }

                        if(tookmove2 == 0){
                            nmoves[1][0] = 0;
                            nmoves[1][1] = 0;
                            nmoves[1][2] = 0;
                            nmoves[1][3] = 0;
                            nmoves[1][4] = 0;
                            nmoves[1][5] = 0;
                        }

                        // upper left jump
                        tookmove2 = 0;
                        if (!(posexp == 15 || posexp == 23 || posexp == 31 || posexp == 39 || posexp == 46 ||
                              posexp == 47 || posexp == 48 || posexp == 49 || posexp == 50 || posexp == 51 ||
                              posexp == 52 || posexp == 53 || posexp == 54 || posexp == 55)) {
                            if ((pos << 17 & sb) || (pos << 17 & db) || (pos << 17 & mb) ||
                                (pos << 17 & sw) || !(pos << 17 & occupied)) {
                                figpos[2] = pos << 17;
                                movepos = pos << 17;

                                // move dw/mw from old pos to new
                                if(!(movepos & occupied)){
                                    if(i==2){
                                        nmoves[2][2] = dw &~ pos;
                                        nmoves[2][0] = sw | movepos | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[2][4] = mw &~ pos;
                                        nmoves[2][0] = sw | movepos;
                                        nmoves[2][1] = sb | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on sw
                                if(movepos & sw){
                                    if(i==2){
                                        nmoves[2][0] = (sw | pos) &~ movepos;
                                        nmoves[2][2] = (dw | movepos) &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[2][0] = sw &~ movepos;
                                        nmoves[2][1] = sb | pos;
                                        nmoves[2][2] = dw | movepos;
                                        nmoves[2][4] = mw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // dw & mw capture sb
                                if(movepos & sb){
                                    if(i==2){
                                        nmoves[2][0] = sw | movepos | pos;
                                        nmoves[2][1] = sb &~ movepos;
                                        nmoves[2][2] = dw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[2][0] = sw | movepos;
                                        nmoves[2][1] = (sb | pos) &~ movepos;
                                        nmoves[2][4] = mw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on db
                                if(movepos & db){
                                    if(i==2){
                                        nmoves[2][2] = dw &~ pos;
                                        nmoves[2][0] = sw | pos;
                                        nmoves[2][3] = db &~ movepos;
                                        nmoves[2][4] = mw | movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[2][4] = (mw|movepos) &~ pos;
                                        nmoves[2][1] = sb | pos;
                                        nmoves[2][3] = db &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                if(movepos & mb){
                                    if(i==2){
                                        nmoves[2][2] = (dw|movepos) &~ pos;
                                        nmoves[2][0] = sw | pos;
                                        nmoves[2][5] = mb &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[2][2] = dw | movepos;
                                        nmoves[2][4] = mw &~ pos;
                                        nmoves[2][1] = sb | pos;
                                        nmoves[2][5] = mb &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                            }
                        }

                        if(tookmove2 == 0){
                            nmoves[2][0] = 0;
                            nmoves[2][1] = 0;
                            nmoves[2][2] = 0;
                            nmoves[2][3] = 0;
                            nmoves[2][4] = 0;
                            nmoves[2][5] = 0;
                        }


                        tookmove2 = 0;
                        if (!(posexp == 6 || posexp == 14 || posexp == 15 || posexp == 22 || posexp == 23 ||
                              posexp == 30 || posexp == 31 || posexp == 38 || posexp == 39 || posexp == 46 ||
                              posexp == 47 || posexp == 53 || posexp == 54 || posexp == 55)) {
                            if ((pos << 10 & sb) || (pos << 10 & db) || (pos << 10 & mb) ||
                                (pos << 10 & sw) || !(pos << 10 & occupied)) {
                                figpos[3] = pos << 10;
                                movepos = pos << 10;

                                // move dw/mw from old pos to new
                                if(!(movepos & occupied)){
                                    if(i==2){
                                        nmoves[3][2] = dw &~ pos;
                                        nmoves[3][0] = sw | movepos | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[3][4] = mw &~ pos;
                                        nmoves[3][0] = sw | movepos;
                                        nmoves[3][1] = sb | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on sw
                                if(movepos & sw){
                                    if(i==2){
                                        nmoves[3][0] = (sw | pos) &~ movepos;
                                        nmoves[3][2] = (dw | movepos) &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[3][0] = sw &~ movepos;
                                        nmoves[3][1] = sb | pos;
                                        nmoves[3][2] = dw | movepos;
                                        nmoves[3][4] = mw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }


                                // dw & mw capture sb
                                if(movepos & sb){
                                    if(i==2){
                                        nmoves[3][0] = sw | movepos | pos;
                                        nmoves[3][1] = sb &~ movepos;
                                        nmoves[3][2] = dw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[3][0] = sw | movepos;
                                        nmoves[3][1] = (sb | pos) &~ movepos;
                                        nmoves[3][4] = mw &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on db
                                if(movepos & db){
                                    if(i==2){
                                        nmoves[3][2] = dw &~ pos;
                                        nmoves[3][0] = sw | pos;
                                        nmoves[3][3] = db &~ movepos;
                                        nmoves[3][4] = mw | movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[3][4] = (mw|movepos) &~ pos;
                                        nmoves[3][1] = sb | pos;
                                        nmoves[3][3] = db &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                if(movepos & mb){
                                    if(i==2){
                                        nmoves[3][2] = (dw|movepos) &~ pos;
                                        nmoves[3][0] = sw | pos;
                                        nmoves[3][5] = mb &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==4){
                                        nmoves[3][2] = dw | movepos;
                                        nmoves[3][4] = mw &~ pos;
                                        nmoves[3][1] = sb | pos;
                                        nmoves[3][5] = mb &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }


                            }
                        }
                        if(tookmove2 == 0){
                            nmoves[3][0] = 0;
                            nmoves[3][1] = 0;
                            nmoves[3][2] = 0;
                            nmoves[3][3] = 0;
                            nmoves[3][4] = 0;
                            nmoves[3][5] = 0;
                        }
                    }
                }


                if(tookmove == 0){
                    for(int s = 0; s<5;s++){
                        nmoves[s][0] = 0;
                        nmoves[s][1] = 0;
                        nmoves[s][2] = 0;
                        nmoves[s][3] = 0;
                        nmoves[s][4] = 0;
                        nmoves[s][5] = 0;
                    }
                }
            }


            if(i == 3 || i == 5){
                int tookmove = 0;

                // check for corner cases
                if(!(posexp == 0 || posexp == 7 || posexp == 56 || posexp == 63)) {
                    // check for bottom row
                    if (!(posexp == 1 || posexp == 2 || posexp == 3 || posexp == 4 || posexp == 5 || posexp == 6)) {
                        int tookmove2 = 0;


                        // check for individual moves
                        if (!(posexp == 13 || posexp == 14 || posexp == 15 || posexp == 22 || posexp == 23 ||
                              posexp == 30 || posexp == 31 || posexp == 38 || posexp == 39 || posexp == 46 ||
                              posexp == 47 || posexp == 54 || posexp == 55 || posexp == 62)) {
                            if ((pos >> 6 & sb) || (pos >> 6 & db) || (pos >> 6 & mb) || (pos >> 6 & sw) ||
                                !(pos >> 6 & occupied)) {
                                figpos[0] = pos >> 6;
                                movepos = pos >> 6;


                                // move dw/mw from old pos to new
                                if(!(movepos & occupied)){
                                    if(i==3){
                                        nmoves[0][3] = db &~ pos;
                                        nmoves[0][1] = sb | movepos | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[0][5] = mb &~ pos;
                                        nmoves[0][1] = sb | movepos;
                                        nmoves[0][0] = sw | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on sb
                                if(movepos & sb){
                                    if(i==3){
                                        nmoves[0][1] = (sb | pos) &~ movepos;
                                        nmoves[0][3] = (db | movepos) &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[0][1] = sb &~ movepos;
                                        nmoves[0][0] = sw | pos;
                                        nmoves[0][3] = db | movepos;
                                        nmoves[0][5] = mb &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // db & mb capture sw
                                if(movepos & sw){
                                    if(i==3){
                                        nmoves[0][0] = sw &~ movepos;
                                        nmoves[0][1] = sb | movepos | pos;
                                        nmoves[0][3] = db &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[0][0] = (sw | pos) &~ movepos;
                                        nmoves[0][1] = sb | movepos;
                                        nmoves[0][5] = mb &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on dw
                                if(movepos & dw){
                                    if(i==3){
                                        nmoves[0][3] = db &~ pos;
                                        nmoves[0][1] = sb | pos;
                                        nmoves[0][2] = dw &~ movepos;
                                        nmoves[0][5] = mb | movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }

                                    if(i==5){
                                        nmoves[0][5] = (mb|movepos) &~ pos;
                                        nmoves[0][0] = sw | pos;
                                        nmoves[0][2] = dw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                if(movepos & mw){
                                    if(i==3){
                                        nmoves[0][3] = (db|movepos) &~ pos;
                                        nmoves[0][1] = sb | pos;
                                        nmoves[0][4] = mw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[0][3] = db | movepos;
                                        nmoves[0][5] = mb &~ pos;
                                        nmoves[0][0] = sw | pos;
                                        nmoves[0][4] = mw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }


                            }
                        }

                        if(tookmove2 == 0){
                            nmoves[0][0] = 0;
                            nmoves[0][1] = 0;
                            nmoves[0][2] = 0;
                            nmoves[0][3] = 0;
                            nmoves[0][4] = 0;
                            nmoves[0][5] = 0;
                        }

                        tookmove2 = 0;
                        if (!(posexp == 8 || posexp == 9 || posexp == 10 || posexp == 11 || posexp == 12 ||
                              posexp == 13 || posexp == 14 || posexp == 15 || posexp == 22 || posexp == 23 ||
                              posexp == 31 || posexp == 39 || posexp == 47 || posexp == 55)) {
                            if ((pos >> 15 & sb) || (pos >> 15 & db) || (pos >> 15 & mb) ||
                                (pos >> 15 & sw) || !(pos >> 15 & occupied)) {
                                figpos[1] = pos >> 15;
                                movepos = pos >> 15;

                                // move dw/mw from old pos to new
                                if(!(movepos & occupied)){
                                    if(i==3){
                                        nmoves[1][3] = db &~ pos;
                                        nmoves[1][1] = sb | movepos | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[1][5] = mb &~ pos;
                                        nmoves[1][1] = sb | movepos;
                                        nmoves[1][0] = sw | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on sb
                                if(movepos & sb){
                                    if(i==3){
                                        nmoves[1][1] = (sb | pos) &~ movepos;
                                        nmoves[1][3] = (db | movepos) &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[1][1] = sb &~ movepos;
                                        nmoves[1][0] = sw | pos;
                                        nmoves[1][3] = db | movepos;
                                        nmoves[1][5] = mb &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // db & mb capture sw
                                if(movepos & sw){
                                    if(i==3){
                                        nmoves[1][0] = sw &~ movepos;
                                        nmoves[1][1] = sb | movepos | pos;
                                        nmoves[1][3] = db &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[1][0] = (sw | pos) &~ movepos;
                                        nmoves[1][1] = sb | movepos;
                                        nmoves[1][5] = mb &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on dw
                                if(movepos & dw){
                                    if(i==3){
                                        nmoves[1][3] = db &~ pos;
                                        nmoves[1][1] = sb | pos;
                                        nmoves[1][2] = dw &~ movepos;
                                        nmoves[1][5] = mb | movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }

                                    if(i==5){
                                        nmoves[1][5] = (mb|movepos) &~ pos;
                                        nmoves[1][0] = sw | pos;
                                        nmoves[1][2] = dw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                if(movepos & mw){
                                    if(i==3){
                                        nmoves[1][3] = (db|movepos) &~ pos;
                                        nmoves[1][1] = sb | pos;
                                        nmoves[1][4] = mw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[1][3] = db | movepos;
                                        nmoves[1][5] = mb &~ pos;
                                        nmoves[1][0] = sw | pos;
                                        nmoves[1][4] = mw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }
                            }
                        }
                        if(tookmove2 == 0){
                            nmoves[1][0] = 0;
                            nmoves[1][1] = 0;
                            nmoves[1][2] = 0;
                            nmoves[1][3] = 0;
                            nmoves[1][4] = 0;
                            nmoves[1][5] = 0;
                        }

                        tookmove2 = 0;
                        if (!(posexp == 8 || posexp == 9 || posexp == 10 || posexp == 11 || posexp == 12 ||
                              posexp == 13 || posexp == 14 || posexp == 15 || posexp == 16 || posexp == 17 ||
                              posexp == 24 || posexp == 32 || posexp == 40 || posexp == 48)) {
                            if ((pos >> 17 & sb) || (pos >> 17 & dw) || (pos >> 17 & mw) ||
                                (pos >> 17 & sw) || !(pos >> 17 & occupied)) {
                                figpos[2] = pos >> 17;
                                movepos = pos >> 17;

                                // move dw/mw from old pos to new
                                if(!(movepos & occupied)){
                                    if(i==3){
                                        nmoves[2][3] = db &~ pos;
                                        nmoves[2][1] = sb | movepos | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[2][5] = mb &~ pos;
                                        nmoves[2][1] = sb | movepos;
                                        nmoves[2][0] = sw | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on sb
                                if(movepos & sb){
                                    if(i==3){
                                        nmoves[2][1] = (sb | pos) &~ movepos;
                                        nmoves[2][3] = (db | movepos) &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[2][1] = sb &~ movepos;
                                        nmoves[2][0] = sw | pos;
                                        nmoves[2][3] = db | movepos;
                                        nmoves[2][5] = mb &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // db & mb capture sw
                                if(movepos & sw){
                                    if(i==3){
                                        nmoves[2][0] = sw &~ movepos;
                                        nmoves[2][1] = sb | movepos | pos;
                                        nmoves[2][3] = db &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[2][0] = (sw | pos) &~ movepos;
                                        nmoves[2][1] = sb | movepos;
                                        nmoves[2][5] = mb &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump db/mb on dw
                                if(movepos & dw){
                                    if(i==3){
                                        nmoves[2][3] = db &~ pos;
                                        nmoves[2][1] = sb | pos;
                                        nmoves[2][2] = dw &~ movepos;
                                        nmoves[2][5] = mb | movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }

                                    if(i==5){
                                        nmoves[2][5] = (mb|movepos) &~ pos;
                                        nmoves[2][0] = sw | pos;
                                        nmoves[2][2] = dw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump db/mb on mw
                                if(movepos & mw){
                                    if(i==3){
                                        nmoves[2][3] = (db|movepos) &~ pos;
                                        nmoves[2][1] = sb | pos;
                                        nmoves[2][4] = mw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[2][3] = db | movepos;
                                        nmoves[2][5] = mb &~ pos;
                                        nmoves[2][0] = sw | pos;
                                        nmoves[2][4] = mw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }
                            }
                        }
                        if(tookmove2 == 0){
                            nmoves[2][0] = 0;
                            nmoves[2][1] = 0;
                            nmoves[2][2] = 0;
                            nmoves[2][3] = 0;
                            nmoves[2][4] = 0;
                            nmoves[2][5] = 0;
                        }

                        tookmove2 = 0;
                        if (!(posexp == 8 || posexp == 9 || posexp == 10 || posexp == 16 || posexp == 17 ||
                              posexp == 24 || posexp == 25 || posexp == 32 || posexp == 33 || posexp == 40 ||
                              posexp == 41 || posexp == 48 || posexp == 49 || posexp == 57)) {
                            if ((pos >> 10 & sb) || (pos >> 10 & db) || (pos >> 10 & mb) ||
                                (pos >> 10 & sw) || !(pos >> 10 & occupied)) {
                                figpos[3] = pos >> 10;
                                movepos = pos >> 10;

                                // move dw/mw from old pos to new
                                if(!(movepos & occupied)){
                                    if(i==3){
                                        nmoves[3][3] = db &~ pos;
                                        nmoves[3][1] = sb | movepos | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[3][5] = mb &~ pos;
                                        nmoves[3][1] = sb | movepos;
                                        nmoves[3][0] = sw | pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on sb
                                if(movepos & sb){
                                    if(i==3){
                                        nmoves[3][1] = (sb | pos) &~ movepos;
                                        nmoves[3][3] = (db | movepos) &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[3][1] = sb &~ movepos;
                                        nmoves[3][0] = sw | pos;
                                        nmoves[3][3] = db | movepos;
                                        nmoves[3][5] = mb &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // db & mb capture sw
                                if(movepos & sw){
                                    if(i==3){
                                        nmoves[3][0] = sw &~ movepos;
                                        nmoves[3][1] = sb | movepos | pos;
                                        nmoves[3][3] = db &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[3][0] = (sw | pos) &~ movepos;
                                        nmoves[3][1] = sb | movepos;
                                        nmoves[3][5] = mb &~ pos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                // jump dw/mw on dw
                                if(movepos & dw){
                                    if(i==3){
                                        nmoves[3][3] = db &~ pos;
                                        nmoves[3][1] = sb | pos;
                                        nmoves[3][2] = dw &~ movepos;
                                        nmoves[3][5] = mb | movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }

                                    if(i==5){
                                        nmoves[3][5] = (mb|movepos) &~ pos;
                                        nmoves[3][0] = sw | pos;
                                        nmoves[3][2] = dw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                                if(movepos & mw){
                                    if(i==3){
                                        nmoves[3][3] = (db|movepos) &~ pos;
                                        nmoves[3][1] = sb | pos;
                                        nmoves[3][4] = mw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                    if(i==5){
                                        nmoves[3][3] = db | movepos;
                                        nmoves[3][5] = mb &~ pos;
                                        nmoves[3][0] = sw | pos;
                                        nmoves[3][4] = mw &~ movepos;
                                        tookmove = 1;
                                        tookmove2 = 1;
                                    }
                                }

                            }
                        }

                        if(tookmove2 == 0){
                            nmoves[3][0] = 0;
                            nmoves[3][1] = 0;
                            nmoves[3][2] = 0;
                            nmoves[3][3] = 0;
                            nmoves[3][4] = 0;
                            nmoves[3][5] = 0;
                        }

                    }


                    if(tookmove == 0){
                        for(int s = 0; s<5;s++){
                            nmoves[s][0] = 0;
                            nmoves[s][1] = 0;
                            nmoves[s][2] = 0;
                            nmoves[s][3] = 0;
                            nmoves[s][4] = 0;
                            nmoves[s][5] = 0;
                        }
                    }

                }
            }

            // save bitboards in moves array
            // max 5 move directions

            for(int move = 0; move<5; move++){
                // 6 figtypes
                if(poscount >= 12){
                    continue;
                }
                for(int figtype = 0; figtype<6; figtype++){
                    moves[poscount][move][figtype] = nmoves[move][figtype];
                }
                if(count_set_bits(moves[poscount][move][0] ^ moves[poscount][move][1] ^ moves[poscount][move][2] ^ moves[poscount][move][3] ^ moves[poscount][move][4] ^ moves[poscount][move][5]) != 0){
                    numMoves ++;
                }
            }
            // number of figures
            poscount++;

        }

    }



    return moves;
}

