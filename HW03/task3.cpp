#include <chrono>
#include <cstddef>
#include <iostream>
#include <omp.h>
#include <random>
#include <ratio>
#include <string>

#include "msort.h"

using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
    std::size_t n = std::stoul(argv[1]);
    int t = std::stoi(argv[2]);
    std::size_t ts = std::stoul(argv[3]);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Array of n random ints in [-1000, 1000]
    int *arr = new int[n];
    for (std::size_t i = 0; i < n; i++) {
        arr[i] = dist(gen);
    }

    // Use t threads for the parallel region inside msort
    omp_set_num_threads(t);

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    duration<double, std::milli> duration_ms;

    start = high_resolution_clock::now();
    msort(arr, n, ts);
    end = high_resolution_clock::now();

    duration_ms = std::chrono::duration_cast<duration<double, std::milli>>(end - start);

    // First element, last element, then time in milliseconds
    std::cout << arr[0] << "\n";
    std::cout << arr[n - 1] << "\n";
    std::cout << duration_ms.count() << "\n";

    delete[] arr;

    return 0;
}
