#include "crossbar.h"

// struct Matrix4_4 {
//     char a00; char a01; char a02; char a03;
//     char a10; char a11; char a12; char a13;
//     char a20; char a21; char a22; char a23;
//     char a30; char a31; char a32; char a33;
// } typedef Matrix4_4_t, *pMatrix4_4;

// Matrix4_4_t crossbar(pMatrix4_4 A, pMatrix4_4 M, pMatrix4_4 out) {

//     // Assuming we are being given the 
//     // elements of A, not A_transpose

//     // Partial Products
//     Matrix4_4_t partial_prod;

//     partial_prod.a00 = 
//         A->a00 * M->a00 +
//         A->a10 * M->a10 +
//         A->a20 * M->a20 +
//         A->a30 * M->a30;
    
//     partial_prod.a01 = 
//         A->a00 * M->a01 +
//         A->a10 * M->a11 +
//         A->a20 * M->a21 +
//         A->a30 * M->a31;
    
//     partial_prod.a02 = 
//         A->a00 * M->a02 +
//         A->a10 * M->a12 +
//         A->a20 * M->a22 +
//         A->a30 * M->a32;
    
//     partial_prod.a03 = 
//         A->a00 * M->a03 +
//         A->a10 * M->a13 +
//         A->a20 * M->a23 +
//         A->a30 * M->a33;
    
//     partial_prod.a10 = 
//         A->a01 * M->a00 +
//         A->a11 * M->a10 +
//         A->a21 * M->a20 +
//         A->a31 * M->a30;

//     partial_prod.a11 = 
//         A->a01 * M->a01 +
//         A->a11 * M->a11 +
//         A->a21 * M->a21 +
//         A->a31 * M->a31;
    
//     partial_prod.a12 = 
//         A->a01 * M->a02 +
//         A->a11 * M->a12 +
//         A->a21 * M->a22 +
//         A->a31 * M->a32;
    
//     partial_prod.a13 = 
//         A->a01 * M->a03 +
//         A->a11 * M->a13 +
//         A->a21 * M->a23 +
//         A->a31 * M->a33;

//     partial_prod.a20 = 
//         A->a02 * M->a00 +
//         A->a12 * M->a10 +
//         A->a22 * M->a20 +
//         A->a32 * M->a30;
    
//     partial_prod.a21 = 
//         A->a02 * M->a01 +
//         A->a12 * M->a11 +
//         A->a22 * M->a21 +
//         A->a32 * M->a31;
    
//     partial_prod.a22 = 
//         A->a02 * M->a02 +
//         A->a12 * M->a12 +
//         A->a22 * M->a22 +
//         A->a32 * M->a32;

//     partial_prod.a23 = 
//         A->a02 * M->a03 +
//         A->a12 * M->a13 +
//         A->a22 * M->a23 +
//         A->a32 * M->a33;
    
//     partial_prod.a30 = 
//         A->a03 * M->a00 +
//         A->a13 * M->a10 +
//         A->a23 * M->a20 +
//         A->a33 * M->a30;
    
//     partial_prod.a31 = 
//         A->a03 * M->a01 +
//         A->a13 * M->a11 +
//         A->a23 * M->a21 +
//         A->a33 * M->a31;
    
//     partial_prod.a32 = 
//         A->a03 * M->a02 +
//         A->a13 * M->a12 +
//         A->a23 * M->a22 +
//         A->a33 * M->a32;

//     partial_prod.a33 = 
//         A->a03 * M->a03 +
//         A->a13 * M->a13 +
//         A->a23 * M->a23 +
//         A->a33 * M->a33;

//     return partial_prod;
// }

// This just does matrix multiply, but it works 
// for the simulation 
void reconfig_crossbar(int n, int* input, int* weights, int* output) {

    // Note that this assumes an nxn matrix
    int sum;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            sum = 0;
            for (int i = 0; i < n; i++) {
                sum += input[row*n+i] * weights[i*n+col];
            }
            output[row*n+col] = sum;
        }
    }
}

// int main() {
//     Matrix4_4_t input;
//     Matrix4_4_t weights;

//     input.a00 = 1; input.a01 = 2; input.a02 = 3; input.a03 = 4;
//     input.a10 = 1; input.a11 = 2; input.a12 = 3; input.a13 = 4;
//     input.a20 = 1; input.a21 = 2; input.a22 = 3; input.a23 = 4;
//     input.a30 = 1; input.a31 = 2; input.a32 = 3; input.a33 = 4;

//     weights.a00 = 1; weights.a01 = 2; weights.a02 = 3; weights.a03 = 4;
//     weights.a10 = 1; weights.a11 = 2; weights.a12 = 3; weights.a13 = 4;
//     weights.a20 = 1; weights.a21 = 2; weights.a22 = 3; weights.a23 = 4;
//     weights.a30 = 1; weights.a31 = 2; weights.a32 = 3; weights.a33 = 4;

//     char* A = malloc(sizeof(char)*16);
//     char* W = malloc(sizeof(char)*16);
//     char* output = malloc(sizeof(char)*16);

//     for (int i = 0; i < 16; i++) {
//         A[i] = i;
//         W[i] = 1;
//     }

//     reconfig_crossbar(4, A, W, output);

//     printf("OUTPUT = \n");
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; j++) {
//             printf("%d ", output[i*4+j]);
//         }
//         printf("\n");
//     }

//     Matrix4_4_t result = crossbar(&input, &weights, NULL);

//     printf("Value of result at a00 = %d\n", result.a00);
//     printf("Value at a33 = %d\n", result.a33);
// }