#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "nonlinear.h"

// DEVICE LENGTH
#define D       1E-9

// MOBILITY OF IONS
#define UV      1E-14 

// MAX AND MIN RESISTANCE
double R_OFF = 1E4;
double R_ON = 1E2;

#define THRESHOLD 1E-5

// WINDOW FUNCTION CONST
#define P       5

// OTHER USEFUL CONSTANTS
#define K       (UV * R_ON)/(D*D) 


double nonlinear(double vDec, double vInc, double dt, double prev_state, double* real_out_voltage) {

    double vIn = vInc - vDec;
    double M = ((R_OFF * prev_state) + (R_ON * (1 - prev_state)));
    double i = vIn / M;
    double new_state = prev_state;

    // Need window functin for nonlinear behavior
    double window = (1 - pow((2*(prev_state+0.0001) - 1), (2*P)));
    double change = K*(i*dt)*window;

    if (fabs(i) < THRESHOLD) {
        printf("NO CHANGE\n");
    }
    else if (i < 0) {
        M = M - change;

        if (M < R_ON) {
            M = R_ON;
        }
        else if (M > R_OFF) {
            M = R_OFF;
        }

        printf("IN i < 0\n");

        new_state = (M - R_ON) / (R_OFF - R_ON);
    }
    else {
        M = M + change;

        if (M < R_ON) {
            M = R_ON;
        }
        else if (M > R_OFF) {
            M = R_OFF;
        }

        new_state = (double)(M - R_ON) / (double)(R_OFF - R_ON);

    }

    printf("i = %f\n", i);
    printf("M = %f\n", M);

    *real_out_voltage = (vIn/M) * M;

    return new_state;

}

// int main() {
//     double testValDec = 0;
//     double testValInc = 3;

//     double cur_state = 0.0;

//     double dt = 0.01;

//     FILE *fileptr;

//     fileptr = fopen("NonlinearData.csv", "w+");

//     fprintf(fileptr, "Step, State\n");
//     fprintf(fileptr, "%d, %f\n", 0, cur_state);

//     for (int i = 1; i <= 1000; i++) {
//         cur_state = nonlinear(testValDec, testValInc, dt, cur_state);
//         printf("State = %f\n", cur_state);
//         fprintf(fileptr, "%d, %f\n", i, cur_state);
//     }

//     fclose(fileptr);
// }