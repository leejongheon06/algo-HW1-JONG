#include "sort.h"
#include <stdlib.h>
#include <string.h>

static void swap_val(void *a, void *b, size_t size) {
    char *tmp = (char *)malloc(size);
    if (!tmp) return;
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

static void qs(char *base, int low, int high, size_t size, SortCompare cmp) {
    if (low < high) {
        char *pivot = base + high * size;
        int i = low;
        for (int j = low; j < high; j++) {
            if (cmp(base + j * size, pivot) <= 0) {
                swap_val(base + i * size, base + j * size, size);
                i++;
            }
        }
        swap_val(base + i * size, base + high * size, size);
        int pi = i;
        qs(base, low, pi - 1, size, cmp);
        qs(base, pi + 1, high, size, cmp);
    }
}

void quickSort(void *base, size_t n, size_t size, SortCompare cmp, SortStats *stats) {
    (void)stats;
    if (n > 1) qs((char*)base, 0, (int)(n - 1), size, cmp);
}
