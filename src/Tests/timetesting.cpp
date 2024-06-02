//
// Created by limin on 6/12/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(){
    time_t currentTime;
    time(&currentTime);

    printf("%s\n",ctime(&currentTime));


}

