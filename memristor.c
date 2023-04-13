#include <iverilog/vpi_user.h>
#include <stdlib.h>

#include <stdlib.h>
#include "nonlinear.h"

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

// This just does matrix multiply, but it works 
// for the simulation 
void reconfig_crossbar(size_t n, char* input, char* weights, char* output) {

    // Note that this assumes an nxn matrix
    char sum;

    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            sum = 0;
            for (size_t i = 0; i < n; i++) {
                sum += input[row*n+i] * weights[i*n+col];
            }
            output[row*n+col] = sum;
        }
    }
}

static int memristor_calltf(PLI_BYTE8* user_data) {

    (void)user_data;

    vpiHandle callh = vpi_handle(vpiSysTfCall, 0);
    vpiHandle argv = vpi_iterate(vpiArgument, callh);
    vpiHandle item;
    vpiHandle item1;
    vpiHandle out;

    item = vpi_scan(argv);
    item1 = vpi_scan(argv);
    out = vpi_scan(argv);
    struct t_vpi_value argval;
    int value;
    int value1;
    struct t_vpi_value out_value;
    out_value.format = vpiIntVal;

    argval.format = vpiIntVal;
    vpi_get_value(item, &argval);
    value = argval.value.integer;
    vpi_get_value(item1, &argval);
    value1 = argval.value.integer;
    vpi_get_value(out, &argval);
    int og_state = argval.value.integer;

    printf("og_state = %d\n", og_state);

    double fixed_state = (double)og_state / (INT16_MAX/2);

    double new_state = nonlinear((double)value, (double)value1, 0.05, fixed_state);

    // printf("new_state = %lf\n", new_state);

    out_value.value.integer = (INT16_MAX/2) * new_state;

    printf("new state should be = %d\n", out_value.value.integer);

    vpi_put_value(out, &out_value, NULL, vpiNoDelay);

    vpi_printf("STATE\n");
    // vpi_printf("RECEIVED = %i\n", value);
    // vpi_printf("RECEIVED ALSO = %i\n", value1);
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