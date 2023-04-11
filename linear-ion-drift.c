#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// DEVICE LENGTH
#define D       1E-09

// MOBILITY OF IONS
#define UV      1E-14 

// MAX AND MIN RESISTANCE
#define R_OFF   1E4
#define R_ON    1e2

#define THRESHOLD 1E-5

// OTHER USEFUL CONSTANTS
#define K       (UV * R_ON)/(D*D) 


double linear(double vDec, double vInc, double dt, double prev_state) {

    double vIn = vInc - vDec;

    double M = ((R_OFF * prev_state) + (R_ON * (1 - prev_state)));

    double i = vIn / M;

    double new_state = prev_state;

    printf("i = %f\n", i);

    double change = K*(i*dt);

    if (fabs(i) < THRESHOLD) {
        printf("NOT CHANGED\n");
        return new_state;
    }
    else if (i < 0) {
        M = M - change;

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
        M = M + change;

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

    double cur_state = 0.0;

    double dt = 0.1;

    for (int i = 0; i < 100; i++) {
        cur_state =  linear(testValDec, testValInc, dt, cur_state);
        printf("State = %f\n", cur_state);
    }
}