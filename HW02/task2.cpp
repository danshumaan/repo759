#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <ratio>
#include <string>

#include "convolution.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int argc, char *argv[]) {
    std::size_t n = std::stoul(argv[1]);
    std::size_t m = std::stoul(argv[2]);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> image_dist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> mask_dist(-1.0f, 1.0f);

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_ms;

    // i) n x n image of random floats in [-10, 10], stored row-major
    float *image = new float[n * n];
    for (std::size_t i = 0; i < n * n; i++) {
        image[i] = image_dist(gen);
    }

    // ii) m x m mask of random floats in [-1, 1], stored row-major
    float *mask = new float[m * m];
    for (std::size_t i = 0; i < m * m; i++) {
        mask[i] = mask_dist(gen);
    }

    float *output = new float[n * n];

    // iii) apply the mask,  convolve
    start = high_resolution_clock::now();
    convolve(image, output, n, mask, m);
    end = high_resolution_clock::now();

    // iv) timing, v) first and vi) last elements
    duration_ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    std::cout << duration_ms.count() << "\n";
    std::cout << output[0] << "\n";
    std::cout << output[n * n - 1] << "\n";

    // vii) memory deallocation
    delete[] image;
    delete[] mask;
    delete[] output;

    return 0;
}