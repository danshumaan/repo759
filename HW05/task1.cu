#include <cstdio>

// Each thread gets the factorial of integers 1 to 8
__global__ void factorial() {
    int a = threadIdx.x + 1;

    int b = 1;
    for (int k = 2; k <= a; k++) {
        b *= k;
    }

    std::printf("%d!=%d\n", a, b);
}

int main() {
    // 1 block with 8 threads
    factorial<<<1, 8>>>();

    cudaDeviceSynchronize();

    return 0;
}
