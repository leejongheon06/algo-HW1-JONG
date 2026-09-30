#ifndef SORT_H
#define SORT_H
#include <stddef.h>

typedef struct SortStats {
    size_t comparisons;
    size_t moves;
    size_t extraBytes;
    size_t maxDepth;
    int stableOk;
} SortStats;

typedef int (*SortCompare)(const void *a, const void *b);

typedef struct SortAlgorithm {
    const char *name;
    const char *timeComplexity;
    const char *spaceComplexity;
    int stable;
    void (*sort)(void *base, size_t n, size_t size, SortCompare cmp, SortStats *stats);
} SortAlgorithm;

extern const SortAlgorithm SORT_ALGORITHMS[];

void quickSort(void *base, size_t n, size_t size, SortCompare cmp, SortStats *stats);
void mergeSort(void *base, size_t n, size_t size, SortCompare cmp, SortStats *stats);
void timSort(void *base, size_t n, size_t size, SortCompare cmp, SortStats *stats);

#endif
