#include "time_count.h"
 

long get_nanos() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}
/*
int main(void)
{   

    long nanos;
    long last_nanos;
    long start;
    nanos = get_nanos();
    last_nanos = nanos;
    start = nanos;
    
    int a = 0;
    for (int i = 0; i < 1000000000; ++i){
        a++;
    }

    last_nanos = get_nanos();   

    long diff_nanos = last_nanos - start;
    long diff_milli = diff_nanos / 1000000;
    int diff_sec = diff_milli / 1000;

    printf("Diff in nano sec: %ld\n", diff_nanos);
    printf("Diff in milli sec: %ld\n", diff_milli);
    printf("Diff in sec: %d\n", diff_sec);

    return EXIT_SUCCESS;
}*/