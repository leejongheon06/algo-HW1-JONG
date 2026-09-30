#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"

#define MAX_N 100000

typedef struct {
    int key;
    int tag;
} Record;

SortStats *current_stats = NULL;

int recordCompare(const void *a, const void *b) {
    if (current_stats) current_stats->comparisons++;
    return ((Record *)a)->key - ((Record *)b)->key;
}

void makeInputRandom(Record *arr, size_t n) {
    for (size_t i = 0; i < n; i++) { arr[i].key = rand() % 100000; arr[i].tag = i; }
}
void makeInputSorted(Record *arr, size_t n) {
    for (size_t i = 0; i < n; i++) { arr[i].key = i; arr[i].tag = i; }
}
void makeInputReversed(Record *arr, size_t n) {
    for (size_t i = 0; i < n; i++) { arr[i].key = n - i; arr[i].tag = i; }
}
void makeInputFewUnique(Record *arr, size_t n) {
    for (size_t i = 0; i < n; i++) { arr[i].key = rand() % 10; arr[i].tag = i; }
}

int checkStability(Record *arr, size_t n) {
    for (size_t i = 1; i < n; i++) {
        if (arr[i-1].key == arr[i].key && arr[i-1].tag > arr[i].tag) return 0;
        if (arr[i-1].key > arr[i].key) return 0;
    }
    return 1;
}

int main(void) {
    size_t sizes[] = {4000, 8000};
    srand(42); 

    printf("=== 정렬 성능 비교 ===\n");
    printf("%-10s %-15s %10s %10s %s\n", "입력", "알고리즘", "시간(ms)", "비교횟수", "안정성");
    printf("--------------------------------------------------------------\n");

    Record *arr = malloc(MAX_N * sizeof(Record));
    if (!arr) return 1;

    for (int si = 0; si < 2; si++) {
        size_t n = sizes[si];
        printf("\n[n = %zu]\n", n);

        for (int t = 0; t < 4; t++) {
            const char *inputName = "";
            switch (t) {
                case 0: inputName = "무작위"; break;
                case 1: inputName = "정렬됨"; break;
                case 2: inputName = "역순"; break;
                case 3: inputName = "중복많음"; break;
            }

            for (size_t ai = 0; ai < 3; ai++) {
                const SortAlgorithm *algo = &SORT_ALGORITHMS[ai];
                SortStats stats = {0,0,0,0,0};
                current_stats = &stats;

                switch (t) {
                    case 0: makeInputRandom(arr, n); break;
                    case 1: makeInputSorted(arr, n); break;
                    case 2: makeInputReversed(arr, n); break;
                    case 3: makeInputFewUnique(arr, n); break;
                }

                clock_t start = clock();
                algo->sort(arr, n, sizeof(Record), recordCompare, &stats);
                clock_t end = clock();
                
                stats.stableOk = checkStability(arr, n);
                double timeMs = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
                
                printf("%-10s %-15s %10.3f %10zu    %s\n",
                       inputName, algo->name, timeMs, stats.comparisons,
                       stats.stableOk ? "yes" : "NO");
            }
            printf("\n");
        }
    }
    free(arr);
    return 0;
}