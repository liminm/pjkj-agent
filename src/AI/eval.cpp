#include "eval.h"

int get_position_value_black(unsigned long long int bb, char type){
    int value = 0;
    unsigned long long int board = bb;
    unsigned int a;
    int i = 0;
    int x;
    int y;
    while (board) {
        a = board & 1;
        if(a == 1){
            x = i/8;
            y = i%8;
            if (type == 's') {
                value += single_table[x][y] + SINGLE_VALUE;
            }else if(type == 'd'){
                value += double_table[x][y] + DOUBLE_VALUE;
            }else{
                value += double_table[x][y] + MIXED_VALUE;
            }
        }
        board >>= 1;
        i++;
    }
    return value;
}

int get_position_value_white(unsigned long long int wb, char type){
    int value = 0;
    unsigned long long int board = wb;
    unsigned int a = 0;
    int i = 63;
    int x;
    int y;
    while (board) {
        a = board & 1;
        if(a == 1){
            x = i/8;
            y = i%8;
            if (type == 's') {
                value += single_table[x][y] + SINGLE_VALUE;
            }else if(type == 'd'){
                value += double_table[x][y] + DOUBLE_VALUE;
            }else{
                value += double_table[x][y] + MIXED_VALUE;
            }
        }
        board >>= 1;
        i--;
    }
    return value;
}


int evalBoard(Node* n, char maxplayer){
    int white_value = 0;
    int black_value = 0;

    white_value += get_position_value_white(n->sw, 's');
    white_value += get_position_value_white(n->dw, 'd');
    white_value += get_position_value_white(n->mw, 'm');
    black_value += get_position_value_black(n->sb, 's');
    black_value += get_position_value_black(n->db, 'd');
    black_value += get_position_value_black(n->mb, 'm');

    if(n->player == 1){
        if(maxplayer == '1'){
            return white_value - black_value;
        } else{
            return black_value - white_value;
        }
    }else{
        if(maxplayer == '1'){
            return black_value - white_value;
        }else{
            return white_value - black_value;
        }
    }

}


unsigned int count_set_bits(unsigned long long int board){

    unsigned int count = lookup[board & 0xff] +
            lookup[(board >> 8) & 0xff] +
            lookup[(board >> 16) & 0xff] +
            lookup[(board >> 24) & 0xff] +
            lookup[(board >> 32) & 0xff] +
            lookup[(board >> 40) & 0xff] +
            lookup[(board >> 48) & 0xff] +
            lookup[(board >> 56) & 0xff];

    return count;
}

unsigned int opponent_can_slay(Node *n, char player){
    unsigned long long int rs = 0;
    unsigned long long int rd = 0;
    unsigned long long int rm = 0;
    unsigned long long int ru = 0;
    unsigned long long int lu = 0;
    unsigned long long int urr = 0;
    unsigned long long int ull = 0;
    unsigned long long int uur = 0;
    unsigned long long int uul = 0;
    unsigned long long int no_ru = 18374969058471772417;
    unsigned long long int no_lu = 18410856566090662016;
    unsigned long long int no_dull = 18428941609300181184;
    unsigned long long int no_durr = 18375534216072069891;
    unsigned long long int no_duul = 18446603888132915328;
    unsigned long long int no_duur = 18446463702556279041;
    unsigned long long int no_rd = 72340172838076927;
    unsigned long long int no_ld = 9259542123273814271;
    unsigned long long int no_ddll = 13889313184910721279;
    unsigned long long int no_ddrr = 217020518514230271;
    unsigned long long int no_dddl = 9259542123273846783;
    unsigned long long int no_dddr = 72340172838141951;


    if(player == '0'){
        //move sb right down, left down
        ru = (n->sb & (~ no_rd)) >> 9;
        lu = (n->sb & (~ no_ld)) >> 7;

        //move mb, db
        urr = ((n->db | n->mb) & (~ no_ddrr)) >> (8 + 2);
        ull = ((n->db | n->mb) & (~ no_ddll)) >> (8 - 2);
        uur = ((n->db | n->mb) & (~ no_dddr)) >> (16 + 1);
        uul = ((n->db | n->mb) & (~ no_dddl)) >> (16 - 1);

        rs = (lu | ru | urr | ull | uul | uur) & n->sw;
        rd = (lu | ru | urr | ull | uul | uur) & n->dw;
        rm = (lu | ru | urr | ull | uul | uur) & n->mw;

    }else{
        //move sw right up, left up
        ru = (n->sw & (~ no_ru)) << 7;
        lu = (n->sw & (~ no_lu)) << 9;

        urr = ((n->dw | n->mw) & (~ no_durr)) << (8 - 2);
        ull = ((n->dw | n->mw) & (~ no_dull)) << (8 + 2);
        uur = ((n->dw | n->mw) & (~ no_duur)) << (16 - 1);
        uul = ((n->dw | n->mw) & (~ no_duul)) << (16 + 1);

        rs = (lu | ru | urr | ull | uul | uur) & n->sb;
        rd = (lu | ru | urr | ull | uul | uur) & n->db;
        rm = (lu | ru | urr | ull | uul | uur) & n->mb;
    }

    if((rd | rm | rs) == 0){
        return 1; //ruhig
    } else return 0; //unruhig
}