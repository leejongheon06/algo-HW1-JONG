#include "sort.h"
#include <stdlib.h>
#include <string.h>

#define MIN_RUN 32

static void insertionSort(char *base, size_t left, size_t right, size_t size, SortCompare cmp) {
    char *key = (char *)malloc(size);
    for (size_t i = left + 1; i <= right; i++) {
        memcpy(key, base + i * size, size);
        size_t j = i;
        while (j > left && cmp(base + (j - 1) * size, key) > 0) {
            memcpy(base + j * size, base + (j - 1) * size, size);
            j--;
        }
        memcpy(base + j * size, key, size);
    }
    free(key);
}

static void merge(char *base, size_t l, size_t m, size_t r, size_t size, SortCompare cmp) {
    size_t n1 = m - l + 1;
    size_t n2 = r - m;
    char *L = (char *)malloc(n1 * size);
    char *R = (char *)malloc(n2 * size);
    for (size_t i = 0; i < n1; i++) memcpy(L + i * size, base + (l + i) * size, size);
    for (size_t j = 0; j < n2; j++) memcpy(R + j * size, base + (m + 1 + j) * size, size);

    size_t i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (cmp(L + i * size, R + j * size) <= 0) {
            memcpy(base + k * size, L + i * size, size);
            i++;
        } else {
            memcpy(base + k * size, R + j * size, size);
            j++;
        }
        k++;
    }
    while (i < n1) { memcpy(base + k * size, L + i * size, size); i++; k++; }
    while (j < n2) { memcpy(base + k * size, R + j * size, size); j++; k++; }
    free(L); free(R);
}

void timSort(void *base, size_t n, size_t size, SortCompare cmp, SortStats *stats) {
    (void)stats;
    if (n <= 1) return;
    char *arr = (char*)base;
    for (size_t i = 0; i < n; i += MIN_RUN) {
        size_t end = (i + MIN_RUN - 1 < n - 1) ? (i + MIN_RUN - 1) : (n - 1);
        insertionSort(arr, i, end, size, cmp);
    }
    for (size_t cur = MIN_RUN; cur < n; cur = 2 * cur) {
        for (size_t left = 0; left < n; left += 2 * cur) {
            size_t mid = left + cur - 1;
            size_t right = ((left + 2 * cur - 1) < (n - 1)) ? (left + 2 * cur - 1) : (n - 1);
            if (mid < right) merge(arr, left, mid, right, size, cmp);
        }
    }
}
