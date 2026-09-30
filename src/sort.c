#include "sort.h"

const SortAlgorithm SORT_ALGORITHMS[] = {
    {"quickSort", "O(n^2)",     "O(log n)", 0, quickSort},
    {"mergeSort", "O(n log n)", "O(n)",     1, mergeSort},
    {"timSort",   "O(n log n)", "O(n)",     1, timSort}
};
