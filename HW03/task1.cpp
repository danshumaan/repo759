#include <chrono>
#include <cstddef>
#include <iostream>
#include <omp.h>
#include <random>
#include <ratio>
#include <string>

#include "matmul.h"

using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
    std::size_t n = std::stoul(argv[1]);
    int t = std::stoi(argv[2]);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    // n x n matrices A and B of random floats in [-1, 1], stored row-major (as in HW02 task3)
    float *A = new float[n * n];
    float *B = new float[n * n];
    for (std::size_t i = 0; i < n * n; i++) {
        A[i] = dist(gen);
        B[i] = dist(gen);
    }

    float *C = new float[n * n];

    // Use t threads for the parallel region inside mmul
    omp_set_num_threads(t);

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_ms;

    start = high_resolution_clock::now();
    mmul(A, B, C, n);
    end = high_resolution_clock::now();

    duration_ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    // First element, last element, then time in milliseconds
    std::cout << C[0] << "\n";
    std::cout << C[n * n - 1] << "\n";
    std::cout << duration_ms.count() << "\n";

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
