#include <algorithm>

#include "msort.h"

// Serial sort used below the threshold: insertion sort, which has no recursive calls.
static void insertion_sort(int *arr, const std::size_t n) {
    for (std::size_t i = 1; i < n; i++) {
        int value = arr[i];
        std::size_t j = i;
        while (j > 0 && arr[j - 1] > value) {
            arr[j] = arr[j - 1]; // shift larger elements one place right
            j--;
        }
        arr[j] = value;
    }
}

// Merges the two sorted halves arr[0, mid) and arr[mid, n) into one sorted run.
// tmp is scratch space of the same length; each call uses only its own part of it.
static void merge(int *arr, int *tmp, const std::size_t mid, const std::size_t n) {
    std::size_t i = 0;   // next element of the left half
    std::size_t j = mid; // next element of the right half
    std::size_t k = 0;   // next free slot in tmp

    while (i < mid && j < n) {
        if (arr[j] < arr[i]) {
            tmp[k++] = arr[j++];
        } else {
            tmp[k++] = arr[i++];
        }
    }
    while (i < mid) {
        tmp[k++] = arr[i++];
    }
    while (j < n) {
        tmp[k++] = arr[j++];
    }

    std::copy(tmp, tmp + n, arr);
}

// Recursive part: sorts arr[0, n) using tmp[0, n) as scratch space.
static void msort_recursive(int *arr, int *tmp, const std::size_t n, const std::size_t threshold) {
    // Below the threshold (or when there is nothing left to split), sort serially
    if (n < threshold || n < 2) {
        insertion_sort(arr, n);
        return;
    }

    std::size_t half = n / 2;

    // Sort the two halves as separate tasks, so idle threads can pick them up
#pragma omp task
    msort_recursive(arr, tmp, half, threshold);

#pragma omp task
    msort_recursive(arr + half, tmp + half, n - half, threshold);

    // Both halves must be sorted before they can be merged
#pragma omp taskwait

    merge(arr, tmp, half, n);
}

void msort(int *arr, const std::size_t n, const std::size_t threshold) {
    if (n < 2) {
        return; // already sorted
    }

    int *tmp = new int[n];

    // Start the thread team; one thread starts the recursion, and the tasks
    // it creates are shared out among all threads in the team
#pragma omp parallel
    {
#pragma omp single
        msort_recursive(arr, tmp, n, threshold);
    }

    delete[] tmp;
}
