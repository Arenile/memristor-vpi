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

// WINDOW FUNCTION CONST
#define P       1

// OTHER USEFUL CONSTANTS
#define K       (UV * R_ON)/(D*D) 


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

    // Need window function for nonlinear behavior

    double window = (1 - pow((2*prev_state - 1), (2*P)));

    printf("WINDOW = %f\n", window);

    double change = K*(i*dt)*window;

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

    double dt = 3.0;

    double prev_state = 0.5;

    double new_val = nonlinear(testValDec, testValInc, dt, prev_state);
    double newer_val = nonlinear(0, 3, dt, new_val);

    printf("Prev state = %f\n", prev_state);

    printf("new_state = %f\n", new_val);

    printf("Even newer state = %f\n", newer_val);
}