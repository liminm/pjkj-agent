#include "printing.h"

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    int p = 0;

    for (i=size-1;i>=0;i--)
    {
        p = 0;
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
            if (p == 7){
                printf("\n");
            }
            p ++;
        }
    }
    puts("");
}