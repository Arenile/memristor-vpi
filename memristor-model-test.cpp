#include <vector>
#include <math.h>
#include <cstdio>
#include <iostream>
#include <fstream>

#define D 1e-9 // Define device length
#define Ron 100
#define Roff 160 * Ron
#define UV 10e-15 // Mobility of ions
#define PI M_PI
#define p 1.0

using namespace std;

float B = 0.f;
float K = 0.f;

void nonlinear()
{
    double t0 = 0;
    float X0 = 0.076;
    vector<double> X;
    X.push_back(X0);
    vector<double> t;
    t.push_back(t0);
    int nsteps = 1000;
    double T = 0.2;
    B = (D * D) / UV;
    K = Ron / B; // constant mentioned in Biolek model
    double dt = (double)T / (nsteps);
    for (int i = 0; i < nsteps; i++)
    {
        t.push_back(t[i] + dt);
    }
    vector<double> V;
    vector<double> M;
    vector<double> I;
    vector<double> W;
    vector<double> dx;
    for (int i = 0; i < t.size(); i++)
    {
        V.push_back(1 * sin(2 * PI * t[i] * 10));        // input voltage
        M.push_back((Ron * X[i]) + (Roff * (1 - X[i]))); // memristance
        I.push_back((1 * sin(2 * PI * t[i] * 10)) /
                    ((Ron * X[i]) + (Roff * (1 - X[i])))); // current
        //W.push_back(wfunction(X[i],p,I[i])); //window function
        dx.push_back(dt * K * I[i] * 1);
        X.push_back(X[i] + dx[i]); // state variable

        printf("State = %f\n", X[i]);
        printf("Memristance = %f\n", M[i]);
        printf("Current = %f\n", I[i]);
        printf("Iteration = %i\n", i);
        printf("\n");
    }

    ofstream dataFile;
    dataFile.open("v-data.csv");
    for (int i = 0; i < t.size(); i++) {
        dataFile << V[i] << ", ";
    }
    dataFile << "\n";
    for (int i = 0; i < t.size(); i++) {
        dataFile << I[i] << ", ";
    }
    dataFile.close();
}

int main()
{
    nonlinear();

    return 0;
}