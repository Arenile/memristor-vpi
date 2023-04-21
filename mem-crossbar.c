#include "nonlinear.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("HOWDY!\n");

    p_Memristor mem1 = malloc(sizeof(Memristor));
    p_Memristor mem2 = malloc(sizeof(Memristor));

    mem1->state = 0.50;
    mem2->state = 0.20;

    printf("mem1 state = %f\n", mem1->state);

    mem1->inDec = malloc(sizeof(double));
    // mem2->inDec = malloc(sizeof(double));

    *(mem1->inDec) = 0.00;

    mem2->inDec = mem1->inDec;

    printf("mem1 inDec = %f\n", *mem1->inDec);
    printf("mem2 inDec = %f\n", *mem2->inDec);

    mem1->inInc = malloc(sizeof(double));

    *(mem1->inInc) = 5.00;
    mem2->inInc = mem1->inInc;

    printf("mem1 inInc = %f\n", *mem1->inInc);
    printf("mem2 inInc = %f\n", *mem2->inInc);

    double* real_out_1 = malloc(sizeof(double));
    double* real_out_2 = malloc(sizeof(double));

    for (int i = 0; i < 100; i++) {
        mem1->state = nonlinear(*mem1->inDec, *mem1->inInc, 0.05, mem1->state, real_out_1);
        mem2->state = nonlinear(*mem2->inDec, *mem2->inInc, 0.05, mem2->state, real_out_2);
    }

    printf("new m1 state = %f\n", mem1->state);
    printf("new m2 state = %f\n", mem2->state);

    printf("real out 1 = %f\n", *real_out_1);
    printf("real out 2 = %f\n", *real_out_2);
}