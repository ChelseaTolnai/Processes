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

#define number_iter 1000000
#define BILLION 1000000000L

int main()
{
	struct timespec start, end;
    int i = 0;
    long long unsigned total = 0;

    while (i < number_iter) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        write(1, NULL, 0);
        clock_gettime(CLOCK_MONOTONIC, &end);

        long long unsigned diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
        total += diff;
        i++;
    }
    
    long long unsigned average = total/number_iter;
	printf("average time = %llu nanoseconds\n", average);

    return 0;
}
