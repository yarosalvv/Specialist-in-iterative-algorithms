#include "permutations.h"

void bubble_sort(int arr[], int size) {
     for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1 ; j++)
            if (arr[j] > arr[j + 1]) 
                swap(&arr[j], &arr[j + 1]);
}

void swap(int *a,int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void copyARR(int arr[], int copy[], int n){
    for (int i = 0; i < n; i++)
        copy[i] = arr[i];
}



void printARR(int arr[], int n){

    for (int h = 0; h < n; h++) 
        printf("%d ", arr[h]);

    printf("\n");
}

void print_callback(int perm[], int n) {
    printARR(perm, n);
}
// ============================================================================
// Задача 2.3: Алгоритм через таблицу инверсий 
// ============================================================================

long factorial(int n) {
    long result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;
    return result;
}

bool is_valid_inversion_table(int inv[], int n) {
    if (!inv || n < 0)
        return false;

    for (int i = 0; i < n; i++)
        if (inv[i] < 0 || inv[i] >= n - i)
            return false;

    return true;
}

void index_to_inversion_table(long index, int inv[], int n) {
    for (int i = 0; i < n; i++) {
        inv[i] = index % (n - i);
        index /= (n - i);
    }
}

void permutation_from_inversion_table(
    int inv[],
    int sorted[],
    int n,
    int result[])
{
    int available[32];   // достаточно для n<=32 (у тебя тесты до 8)

    for (int i = 0; i < n; i++)
        available[i] = sorted[i];

    int size = n;

    for (int i = 0; i < n; i++) {

        int idx = inv[i];

        result[i] = available[idx];

        for (int j = idx; j < size - 1; j++)
            available[j] = available[j + 1];

        size--;
    }
}

void permutations_inversion_table(int arr[], int n,
                                  void (*callback)(int perm[], int n))
{
    if (n < 0 || !callback)
        return;

    if (n == 0) {
        callback(arr, 0);
        return;
    }

    int *sorted = (int*)malloc(n * sizeof(int));
    if (!sorted)
        return;

    copyARR(arr, sorted, n);
    bubble_sort(sorted, n);

    int *inv = (int*)malloc(n * sizeof(int));
    int *result = (int*)malloc(n * sizeof(int));

    if (!inv || !result) {
        free(sorted);
        free(inv);
        free(result);
        return;
    }

    long total = factorial(n);

    for (long index = 0; index < total; index++) {

        index_to_inversion_table(index, inv, n);

        permutation_from_inversion_table(
            inv,
            sorted,
            n,
            result);

        callback(result, n);
    }

    free(sorted);
    free(inv);
    free(result);
}
