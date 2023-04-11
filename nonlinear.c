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
#define P       2

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

    // Need window function for nonlinear behavior

    double window = (1 - pow((2*(prev_state+0.00001) - 1), (2*P)));

    double change = K*(i*dt)*window;

    // printf("change = %f\n", change);
    // printf("i = %f\n", i);
    // printf("M = %f\n", M);
    // printf("window = %f\n", window);

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
        cur_state = nonlinear(testValDec, testValInc, dt, cur_state);
        printf("State = %f\n", cur_state);
    }
}