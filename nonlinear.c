#include <stdlib.h>

// DEVICE LENGTH
#define D       1e-09

// MOBILITY OF IONS
#define UV      1e-12  

// MAX AND MIN RESISTANCE
#define R_OFF   1e6
#define R_ON    1e2

// OTHER USEFUL CONSTANTS
#define B       (D * D) / UV
#define K       R_ON / B


float nonlinear(float vDec, float vInc, float dt, float prev_state) {

    float vIn = vInc - vDec;

    float M = ((R_ON * prev_state) + (R_OFF * (1 - prev_state)));

    float i = vIn / M;

    // Window function should go here but instead...

    // if i < * THRESHOLD *
    // then not hight enough current to change M
    // else
    // M should change based on how high i is and
    // some other constants 

    float new_state = prev_state;

    if (abs(i) < B) {
        return new_state;
    }
    else if (i < B) {
        M = M - (i * dt);

        new_state = M / (R_OFF - R_ON);
        return new_state;
    }
    else {
        M = M + (i * dt);

        new_state = M / (R_OFF - R_ON);
        return new_state;
    }

    
    float X0 = 0.076; // init state var

    int nsteps = 1000; // may redefine this
    
    double T = 0.2;

    double dt = (double)T / nsteps; 

}