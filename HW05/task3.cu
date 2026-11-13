#include <cmath>
#include <iostream>
#include <random>
#include <string>

#include "vscale.cuh"

// Threads per block for the vscale launch. 
#ifndef THREADS_PER_BLOCK
#define THREADS_PER_BLOCK 512
#endif

int main(int argc, char *argv[]) {
    unsigned int n = std::stoul(argv[1]);

    // a in [-10.0, 10.0], b in [0.0, 1.0].
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist_a(-10.0f, std::nextafter(10.0f, 11.0f));
    std::uniform_real_distribution<float> dist_b(0.0f, std::nextafter(1.0f, 2.0f));

    float *a = new float[n];
    float *b = new float[n];
    for (unsigned int i = 0; i < n; i++) {
        a[i] = dist_a(gen);
        b[i] = dist_b(gen);
    }

    // Copy arrays to GPU
    float *dA;
    float *dB;
    cudaMalloc((void **)&dA, n * sizeof(float));
    cudaMalloc((void **)&dB, n * sizeof(float));
    cudaMemcpy(dA, a, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dB, b, n * sizeof(float), cudaMemcpyHostToDevice);

    // Give every element its own thread
    unsigned int threads_per_block = THREADS_PER_BLOCK;
    unsigned int num_blocks = (n + threads_per_block - 1) / threads_per_block;

    // Time kernel, using CUDA events
    cudaEvent_t start;
    cudaEvent_t stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    vscale<<<num_blocks, threads_per_block>>>(dA, dB, n);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float ms = 0.0f;
    cudaEventElapsedTime(&ms, start, stop);

    // Copy result back to host
    cudaMemcpy(b, dB, n * sizeof(float), cudaMemcpyDeviceToHost);

    // Timing
    std::cout << ms << "\n";
    std::cout << b[0] << "\n";
    std::cout << b[n - 1] << "\n";

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(dA);
    cudaFree(dB);
    delete[] a;
    delete[] b;

    return 0;
}
