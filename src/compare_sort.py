import time
import random
import sys

# 파이썬 재귀 한도 늘리기 (퀵 정렬 최악의 경우 대비)
sys.setrecursionlimit(20000)

# 1. 퀵 정렬 (Quick Sort)
def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    
    pivot = arr[0]
    left = [x for x in arr[1:] if x <= pivot]
    right = [x for x in arr[1:] if x > pivot]
    return quick_sort(left) + [pivot] + quick_sort(right)

# 2. 병합 정렬 (Merge Sort)
def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    
    merged = []
    l = h = 0
    while l < len(left) and h < len(right):
        if left[l] < right[h]:
            merged.append(left[l])
            l += 1
        else:
            merged.append(right[h])
            h += 1
    merged += left[l:]
    merged += right[h:]
    return merged

# 3. 팀 정렬 
MIN_RUN = 32

def insertion_sort(arr, left, right):
    for i in range(left + 1, right + 1):
        key = arr[i]
        j = i - 1
        while j >= left and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def merge(arr, l, m, r):
    left = arr[l:m + 1]
    right = arr[m + 1:r + 1]
    i = 0
    j = 0
    k = l
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            arr[k] = left[i]
            i += 1
        else:
            arr[k] = right[j]
            j += 1
        k += 1
    while i < len(left):
        arr[k] = left[i]
        k += 1
        i += 1
    while j < len(right):
        arr[k] = right[j]
        k += 1
        j += 1

def tim_sort(arr):
    n = len(arr)
    for i in range(0, n, MIN_RUN):
        insertion_sort(arr, i, min((i + MIN_RUN - 1), n - 1))
    size = MIN_RUN
    while size < n:
        for left in range(0, n, 2 * size):
            mid = min(n - 1, left + size - 1)
            right = min((left + 2 * size - 1), (n - 1))
            if mid < right:
                merge(arr, left, mid, right)
        size = 2 * size
    return arr

# --- 성능 측정 메인 함수 ---
def measure_time(sort_func, data, name, condition):
    
    arr = data.copy()
    
    start = time.time()
    if name == "Tim Sort":
        tim_sort(arr)
    else:
        sort_func(arr)
    end = time.time()
    
    print(f"[{condition}] {name} 소요 시간: {end - start:.5f} 초")

if __name__ == "__main__":
    
    DATA_SIZE = 2000 
    print(f"=== 정렬 성능 비교 (데이터 크기: {DATA_SIZE}개) ===\n")
    
   
    random_data = [random.randint(1, 100000) for _ in range(DATA_SIZE)]
    
    sorted_data = sorted(random_data)
   
    reverse_data = sorted_data[::-1]
    
    conditions = [
        ("랜덤 데이터", random_data),
        ("이미 정렬된 데이터", sorted_data),
        ("역순 데이터", reverse_data)
    ]
    
    for cond_name, data in conditions:
        print(f"--- {cond_name} ---")
        measure_time(quick_sort, data, "Quick Sort", cond_name)
        measure_time(merge_sort, data, "Merge Sort", cond_name)
        measure_time(tim_sort, data, "Tim Sort", cond_name)
        print()
