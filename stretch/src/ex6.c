/*
Write a program that will find the average time it takes for your computer
to make a system call an empty write to stdout. Your program should use the 
`clock_gettime` procedure to time how long a single system call takes. It'll 
do this for one million iterations, and then find the average of all of those 
iterations in nanoseconds.
For some helpful documentation and examples of using time-related system calls,
visit this site: https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/gettime.html
While the linked site does say that `clock_gettime()` does not work on OSX, this 
turns out to only be the case for OSX versions < 10.12. Anything later than that 
and `clock_gettime()` should work just fine. 
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define number_iter 10
#define BILLION 1000000000L

int main()
{
    // Your code here
    long sum_diff;
    struct timespec start, end;
    char *myargs[3];
    myargs[0] = strdup("./bankers");
    myargs[1] = strdup("40");
    myargs[2] = NULL;

    for (long i = 1; i <= number_iter; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        execvp(myargs[0], myargs);
        clock_gettime(CLOCK_MONOTONIC, &end);
        sum_diff += BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    }
    printf("Elasped time %f\n", (float) (sum_diff / number_iter));

    sum_diff = 0;
    myargs[0] = strdup("./bankers1");

    for (long j = 1; j <= number_iter; j++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        execvp(myargs[0], myargs);
        clock_gettime(CLOCK_MONOTONIC, &end);
        sum_diff += BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    }
    printf("Elasped time %f\n", (float) (sum_diff / number_iter));
    return 0;
}