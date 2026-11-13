#include "vscale.cuh"

// Each thread does one op: b[i] *= a[i].
// Last block can go past array length, so threads with i >= n do nothing.
__global__ void vscale(const float *a, float *b, unsigned int n) {

    unsigned int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n) {
        b[i] = a[i] * b[i];
    }
}
