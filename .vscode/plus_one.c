
#include "permutations.h"
// ============================================================================
// Задача 2.4: Алгоритм "Плюс-один" (инкрементальный)
// ============================================================================

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


long factorial(int n) {
    long result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;
    return result;
}
// ============================================================================
// Задача 2.4: Алгоритм "Плюс-один" (инкрементальный)
// ============================================================================

void build_permutation_from_indices(int sorted[], int indices[], 
                                        int n, int result[], int temp[]) {
    copyARR(sorted, temp, n);

    int size = n;

    for (int i = 0; i < n; i++) {

        int idx = indices[i];

        result[i] = temp[idx];

        for (int j = idx; j < size - 1; j++)
            temp[j] = temp[j + 1];

        size--;
    }
}

void increment_factoradic(int indices[], int n) {

    for (int i = n - 1; i >= 0; i--) {

        indices[i]++;

        if (indices[i] < n - i)
            return;

        indices[i] = 0;
    }
}

void permutations_plus_one(int arr[], int n,
                          void (*callback)(int perm[], int n))
{
    if (!callback)
        return;

    if (n == 0) {
        callback(arr, 0);
        return;
    }

    int *sorted = (int*)malloc(n * sizeof(int));
    int *indices = (int*)malloc(n * sizeof(int));
    int *result  = (int*)malloc(n * sizeof(int));
    int *temp    = (int*)malloc(n * sizeof(int));

    if (!sorted || !indices || !result || !temp) {
        free(sorted);
        free(indices);
        free(result);
        free(temp);
        return;
    }

    copyARR(arr, sorted, n);
    bubble_sort(sorted, n);

    for (int i = 0; i < n; i++)
        indices[i] = 0;

    long total = factorial(n);

    for (long count = 0; count < total; count++) {

        build_permutation_from_indices(
            sorted,
            indices,
            n,
            result,
            temp);

        callback(result, n);

        increment_factoradic(indices, n);
    }

    free(sorted);
    free(indices);
    free(result);
    free(temp);
}
