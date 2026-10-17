#include <chrono>
#include <cstddef>
#include <iostream>
#include <omp.h>
#include <random>
#include <ratio>
#include <string>

#include "convolution.h"

using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
    std::size_t n = std::stoul(argv[1]);
    int t = std::stoi(argv[2]);
    const std::size_t m = 3; // the mask is always 3 x 3

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> image_dist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> mask_dist(-1.0f, 1.0f);

    // n x n image of random floats in [-10, 10], stored row-major (as in HW02 task2)
    float *image = new float[n * n];
    for (std::size_t i = 0; i < n * n; i++) {
        image[i] = image_dist(gen);
    }

    // 3 x 3 mask of random floats in [-1, 1], stored row-major (as in HW02 task2)
    float *mask = new float[m * m];
    for (std::size_t i = 0; i < m * m; i++) {
        mask[i] = mask_dist(gen);
    }

    float *output = new float[n * n];

    // Use t threads for the parallel region inside convolve
    omp_set_num_threads(t);

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_ms;

    start = high_resolution_clock::now();
    convolve(image, output, n, mask, m);
    end = high_resolution_clock::now();

    duration_ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    // First element, last element, then time in milliseconds
    std::cout << output[0] << "\n";
    std::cout << output[n * n - 1] << "\n";
    std::cout << duration_ms.count() << "\n";

    delete[] image;
    delete[] mask;
    delete[] output;

    return 0;
}
