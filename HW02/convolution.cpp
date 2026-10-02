#include "convolution.h"

static float pixel(const float *image, std::size_t n, long i, long j) {
    bool row_ok = (i >= 0 && i < (long)n);
    bool col_ok = (j >= 0 && j < (long)n);

    if (row_ok && col_ok) {
        return image[i * n + j];   // inside the image
    }
    if (row_ok || col_ok) {
        return 1.0f;               // edge: exactly one index is out of range
    }
    return 0.0f;
}

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m) {
    long offset = (m - 1) / 2;

    for (std::size_t x = 0; x < n; x++) {
        for (std::size_t y = 0; y < n; y++) {
            float sum = 0.0f;
            for (std::size_t i = 0; i < m; i++) {
                for (std::size_t j = 0; j < m; j++) {
                    long row = (long)x + (long)i - offset;
                    long col = (long)y + (long)j - offset;
                    sum += mask[i * m + j] * pixel(image, n, row, col);
                }
            }
            output[x * n + y] = sum;
        }
    }
}