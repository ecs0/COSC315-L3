/*
 * answer = ((a - 2) * 2 + (b + 1) * 3) * 2.7  + ((a + c) + d * 2) ^ e
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char * args[]) {

    double a, b, c, d, e, answer, t1, t2, t3, t4, t5;
    int p[2], q[2], r[2];
    char msg[100];
    a = atof(args[1]);
    b = atof(args[2]);
    c = atof(args[3]);
    d = atof(args[4]);
    e = atof(args[5]);

    pipe(p);
    pipe(q);
    pipe(r);

    if (!fork()) {
        t1 = a - 2;
        t1 = t1 * 2;
        read(q[0], &t2, sizeof(double));
        t1 = t1 + t2;
        t1 = t1 * 2.7;
        write(p[1], &t1, sizeof(double));
        return 0;
    }

    if (!fork()) {
        t2 = b + 1;
        t2 = t2 * 3;
        write(q[1], &t2, sizeof(double));
        return 0;
    }

    if(!fork()) {
        t3 = d * 2;
        write(r[1], &t3, sizeof(double));
        return 0;
    }

    t5 = a + c;

    read(r[0], &t3, sizeof(double));

    t5 = t5 + t3;
    t5 = pow(t5, e);

    read(p[0], &t1, sizeof(double));

    t4 = t1 + t5;
    answer = t4;

    sprintf(msg, "((%.1f - 2) * 2 + (%.1f + 1) * 3) * 2.7 + ((%.1f + %.1f) + %.1f * 2) ^ %.1f = %.3f\n", a, b, a, c, d, e, answer);
    puts(msg);
    return 0;
}
