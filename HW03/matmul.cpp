#include <algorithm>

#include "matmul.h"

// Parallel version of mmul2 from HW02: loop order (i, k, j).
// Each thread gets a block of rows i, and only that thread writes to row i of C,
// so threads never write to the same element and no locking is needed.
void mmul(const float *A, const float *B, float *C, const std::size_t n) {
#pragma omp parallel for
    for (std::size_t i = 0; i < n; i++) {
        std::fill(C + i * n, C + (i + 1) * n, 0.0f); // start row i of C at zero so += works

        for (std::size_t k = 0; k < n; k++) {
            for (std::size_t j = 0; j < n; j++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}
