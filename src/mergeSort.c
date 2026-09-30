#include "sort.h"
#include <stdlib.h>
#include <string.h>

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

static void ms(char *base, size_t l, size_t r, size_t size, SortCompare cmp) {
    if (l < r) {
        size_t m = l + (r - l) / 2;
        ms(base, l, m, size, cmp);
        ms(base, m + 1, r, size, cmp);
        merge(base, l, m, r, size, cmp);
    }
}

void mergeSort(void *base, size_t n, size_t size, SortCompare cmp, SortStats *stats) {
    (void)stats;
    if (n > 1) ms((char*)base, 0, n - 1, size, cmp);
}
