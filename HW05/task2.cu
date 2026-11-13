#include <iostream>
#include <random>

// Each thread get a * x + y, where x is threadIdx and y is blockIdx
__global__ void compute(int *dA, int a) {
    int x = threadIdx.x;
    int y = blockIdx.x;

    dA[blockIdx.x * blockDim.x + threadIdx.x] = a * x + y;
}

int main() {
    const int num_blocks = 2;
    const int threads_per_block = 8;
    const int n = num_blocks * threads_per_block; // 16 entries

    // Allocate on device
    int *dA;
    cudaMalloc((void **)&dA, n * sizeof(int));

    // Random integer a in [1, 10]
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    int a = dist(gen);

    // 2 blocks with 8 threads each
    compute<<<num_blocks, threads_per_block>>>(dA, a);

    // Copy the results back into the host array
    int hA[n];
    cudaMemcpy(hA, dA, n * sizeof(int), cudaMemcpyDeviceToHost);

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            std::cout << " ";
        }
        std::cout << hA[i];
    }
    std::cout << "\n";

    cudaFree(dA);

    return 0;
}
