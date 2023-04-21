double nonlinear(double vDec, double vInc, double dt, double prev_state, double* real_out_voltage);

struct memristor {
    double state;
    double* inDec;
    double* inInc;
} typedef Memristor, *p_Memristor;