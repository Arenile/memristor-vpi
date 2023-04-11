#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// DEVICE LENGTH
#define D       1e-09

// MOBILITY OF IONS
#define UV      1e-12  

// MAX AND MIN RESISTANCE
#define R_OFF   1E4
#define R_ON    1e2

#define THRESHOLD 1E-5

// OTHER USEFUL CONSTANTS
#define B       (D * D) / UV
#define K       R_ON / B


double nonlinear(double vDec, double vInc, double dt, double prev_state) {

    double vIn = vInc - vDec;

    double M = ((R_OFF * prev_state) + (R_ON * (1 - prev_state)));

    double i = vIn / M;

    // Window function should go here but instead...

    // if i < * THRESHOLD *
    // then not hight enough current to change M
    // else
    // M should change based on how high i is and
    // some other constants 

    double new_state = prev_state;

    printf("i = %f\n", i);

    if (fabs(i) < THRESHOLD) {
        printf("NOT CHANGED\n");
        return new_state;
    }
    else if (i < 0) {
        M = M - (i * dt);

        if (M < R_ON) {
            M = R_ON;
        }
        else if (M > R_OFF) {
            M = R_OFF;
        }

        printf("M = %f\n", M);

        new_state = (M - R_ON) / (R_OFF - R_ON);
        return new_state;
    }
    else {
        M = M + (i * dt);

        if (M < R_ON) {
            M = R_ON;
        }
        else if (M > R_OFF) {
            M = R_OFF;
        }

        printf("M = %f\n", M);

        new_state = (M - R_ON) / (R_OFF - R_ON);
        return new_state;
    }

}

int main() {
    double testValDec = 0;
    double testValInc = 3;

    double dt = 1000000;

    double prev_state = 0.5;

    double new_val = nonlinear(testValDec, testValInc, dt, prev_state);
    double newer_val = nonlinear(0, 3, dt, new_val);

    printf("Prev state = %f\n", prev_state);

    printf("new_state = %f\n", new_val);

    printf("Even newer state = %f\n", newer_val);
}