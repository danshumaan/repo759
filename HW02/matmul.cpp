#include <algorithm>

#include "matmul.h"

// Loop order (i, j, k)
void mmul1(const double* A, const double* B, double* C, const unsigned int n) {
    std::fill(C, C + n * n, 0.0);   // start C at zero so += works

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            for (unsigned int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

// Loop order (i, k, j): the two inner loops of mmul1 swapped
void mmul2(const double* A, const double* B, double* C, const unsigned int n) {
    std::fill(C, C + n * n, 0.0);   // start C at zero so += works

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int k = 0; k < n; k++) {
            for (unsigned int j = 0; j < n; j++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

// Loop order (j, k, i): the outer loop of mmul1 moved innermost
void mmul3(const double* A, const double* B, double* C, const unsigned int n) {
    std::fill(C, C + n * n, 0.0);   // start C at zero so += works

    for (unsigned int j = 0; j < n; j++) {
        for (unsigned int k = 0; k < n; k++) {
            for (unsigned int i = 0; i < n; i++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

// Same loop order as mmul1, but A and B are std::vector<double>
void mmul4(const std::vector<double>& A, const std::vector<double>& B, double* C, const unsigned int n) {
    std::fill(C, C + n * n, 0.0);   // start C at zero so += works

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            for (unsigned int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}