/*
 * answer = ((a - 2) * 2 + (b + 1) * 3) * 2.7  + ((a + c) + d * 2) ^ e
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char * args[]) {

    double a, b, c, d, e, answer, t1, t2, t3, t4, t5;
    int p[2], q[2], r[2], s[2], t[2];

    a = atof(args[1]);            /* extract numbers from command line args */
    b = atof(args[2]);
    c = atof(args[3]);
    d = atof(args[4]);
    e = atof(args[5]);
    pipe(p);
    pipe(q);
    pipe(r);
    pipe(s);
    pipe(t);

    if (!fork()) {
        t1 = a - 2;
        t1 = t1 * 2;
        write(p[1], &t1, sizeof(double));
        return 0;
    }
    if (!fork()) {
        t2 = b + 1;
        t2 = t2 * 3;
        write(q[1], &t2, sizeof(double));      /* pipe result to parent */
        return 0;
    }

    t3 = a + c;
    t3 = t3 * 2.7;


//    t4 =
//    t4 = t4 * 2.7;
    t5 = pow((t3 + d * 2), e);

    answer = t4 + t5;

    printf("((%f - 2) * 2 + (%f + 1) * 3) * 2.7 + ((%f + %f) + %f * 2) ^ %f = %f\n", a, b, a, c, d, e, answer);
    return 0;
}