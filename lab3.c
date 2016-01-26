#include <stdio.h>
#include <stdlib.h>    // For atoi
#include <unistd.h>    // For fork(), pipe(), read(), write()

int main(int argc, char * args[]) {

    double a, b, c, d, answer, t1, t2;
    int p[2];
    int bufsize;

    a = atoi(args[1]);            /* extract numbers from command line args */
    b = atoi(args[2]);
    c = atoi(args[3]);
    d = atoi(args[4]);
    pipe(p);                      /* set up pipe */
    bufsize = sizeof(int);        /* get size of data to be piped */

    if (!fork()) {                /* child's code */
        t1 = c * d;                     /* calculate part of answer */
        write(p[1], &t1, bufsize);      /* pipe result to parent */
        return 0;
    }
    /* parent's code */
    t2 = a - b;                       /* calculate part of answer */
    read(p[0], &t1, bufsize);         /* get result from pipe */
    answer = t2 + t1;                 /* calculate answer */

    printf("%f - %f + %f * %f = %f\n", a, b, c, d, answer);
    return 0;
}