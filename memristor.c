#include <vpi_user.h>

#include <stdlib.h>

// Function prototypes
void memristor_register(void);
void (*vlog_startup_routines[])(void);
static int memristor_compiletf(PLI_BYTE8* user_data);
static int memristor_calltf(PLI_BYTE8* user_data);

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

/* Here we can make calls upon compiling in the verilog
*/
static int memristor_compiletf(PLI_BYTE8* user_data) {

    (void)user_data;

    return 0;
}

static int memristor_calltf(PLI_BYTE8* user_data) {

    (void)user_data;

    vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
    vpiHandle argv = vpi_iterate(vpiArgument, callh);
    vpiHandle rInc;
    vpiHandle rDec;

    rInc = vpi_scan(argv);
    rDec = vpi_scan(argv);
    struct t_vpi_value argval;
    int value;
    int value1;
    struct t_vpi_value out_value;
    out_value.format = vpiIntVal;

    argval.format = vpiIntVal;
    vpi_get_value(rInc, &argval);
    value = argval.value.integer;
    vpi_get_value(rDec, &argval);
    value1 = argval.value.integer;

    out_value.value.integer = nonlinear(value, value1);

    vpi_put_value(rDec, &out_value, NULL, vpiNoDelay);

    vpi_printf("HELLO VERILOG!\n");
    vpi_printf("RECEIVED = %i\n", value);
    vpi_printf("RECEIVED ALSO = %i\n", value1);
    return 1;
}

void memristor_register(void) {
    s_vpi_systf_data tf_data;

    tf_data.type = vpiSysTask;
    tf_data.tfname = "$memristor";
    tf_data.calltf = memristor_calltf;
    tf_data.compiletf = memristor_compiletf;
    tf_data.sizetf = 0;
    tf_data.user_data = "$memristor";
    vpiHandle res = vpi_register_systf(&tf_data);
    vpip_make_systf_system_defined(res);
}

void (*vlog_startup_routines[])(void) = {
    memristor_register,
    0
};

void nonlinear(float vDec, float vInc) {
    double t0 = 0;
    float X0 = 0.076; // init state var

    int nsteps = 1000; // may redefine this
    
    double T = 0.2;

    double dt = (double)T / nsteps;

}