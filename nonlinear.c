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


void nonlinear(float vDec, float vInc) {
    double t0 = 0;
    float X0 = 0.076; // init state var

    int nsteps = 1000; // may redefine this
    
    double T = 0.2;

    double dt = (double)T / nsteps;

}