#include <string>
#include <random>
#include <chrono>
#include "scan.h"
#include <iostream>
using std::chrono::high_resolution_clock;
using std::chrono::duration;


int main(int argc, char *argv[]) {
    std::size_t n = std::stoul(argv[1]);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_ms;

    // i) creates the array
    float *arr = new float[n];
    for (std::size_t i = 0; i < n; i++) {
        arr[i]  = dist(gen);
    }

    float *output = new float[n];

    // ii) scanning
    start = high_resolution_clock::now();
    scan(arr, output, n);
    end = high_resolution_clock::now();
    
    // iii) timing, iv) first and v) last elements
    duration_ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);
    std::cout << duration_ms.count() << "\n";
    std::cout << output[0] << "\n";
    std::cout << output[n-1] << "\n";

    // vi) memory deallocation
    delete[] arr;
    delete[] output;

    return 0;
}