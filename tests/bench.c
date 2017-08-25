#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../bitforce_bitset.h"

double
time_diff(struct timeval *x, struct timeval *y)
{
    struct timeval  diff;

    diff.tv_sec = y->tv_sec - x->tv_sec;
    diff.tv_usec = y->tv_usec - x->tv_usec;
    while (diff.tv_usec < 0) {
        diff.tv_usec += 1000000;
        diff.tv_sec -= 1;
    }
    return (double) diff.tv_sec + (double) diff.tv_usec / 1000000.0;
}

int
main(int argc, char **argv)
{
    bitforce_bitset_t b1;
    bitforce_bitset_init(&b1, 0);
    bitforce_bitset_t b2;
    bitforce_bitset_init(&b2, 0);
    /**/
    srand(0);
    for (int i = 0; i < 1000000; i++) {
        if (rand() & 1) {
            bitforce_bitset_set(&b1, i);
        }
        if (rand() & 1) {
            bitforce_bitset_set(&b2, i);
        }
    }
    /**/
    struct timeval begin;
    gettimeofday(&begin, NULL);
    for (int n = 0; n < 100000; n++) {
        // bitforce_bitset_set(&b1, rand() % 1000000);
        // bitforce_bitset_set(&b2, rand() % 1000000);
        bitforce_bitset_xor(&b1, &b2);
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    printf("sec: %f\n", time_diff(&begin, &end));

    exit(0);
}
