#include <chrono>
#include <iostream>
#include <random>
#include <ratio>
#include <vector>

#include "matmul.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main() {
    const unsigned int n = 1024;

    // Random values for A and B
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    // A and B as plain arrays (for mmul1, mmul2, mmul3), stored row-major
    double *A = new double[n * n];
    double *B = new double[n * n];
    for (unsigned int i = 0; i < n * n; i++) {
        A[i] = dist(gen);
        B[i] = dist(gen);
    }

    // The same A and B as vectors (for mmul4)
    std::vector<double> A_vec(A, A + n * n);
    std::vector<double> B_vec(B, B + n * n);

    double *C = new double[n * n];

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_ms;

    // Number of rows
    std::cout << n << "\n";

    // mmul1
    start = high_resolution_clock::now();
    mmul1(A, B, C, n);
    end = high_resolution_clock::now();
    duration_ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    std::cout << duration_ms.count() << "\n";
    std::cout << C[n * n - 1] << "\n";

    // mmul2
    start = high_resolution_clock::now();
    mmul2(A, B, C, n);
    end = high_resolution_clock::now();
    duration_ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    std::cout << duration_ms.count() << "\n";
    std::cout << C[n * n - 1] << "\n";

    // mmul3
    start = high_resolution_clock::now();
    mmul3(A, B, C, n);
    end = high_resolution_clock::now();
    duration_ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    std::cout << duration_ms.count() << "\n";
    std::cout << C[n * n - 1] << "\n";

    // mmul4
    start = high_resolution_clock::now();
    mmul4(A_vec, B_vec, C, n);
    end = high_resolution_clock::now();
    duration_ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    std::cout << duration_ms.count() << "\n";
    std::cout << C[n * n - 1] << "\n";

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}