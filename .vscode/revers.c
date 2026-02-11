




// ============================================================================
// ЗАДАЧА 2.5: Алгоритм "Реверсивный Нарайана"
// ============================================================================

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


void reverseTail(int arr[], int start, int end) {
    // Разворачиваем часть массива от start до end
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

void printARR(int arr[], int n){

    for (int h = 0; h < n; h++) 
        printf("%d ", arr[h]);

    printf("\n");
}

void copyARR(int arr[], int copy[], int n){
    for (int i = 0; i < n; i++)
        copy[i] = arr[i];
}


void print_callback(int perm[], int n) {
    printARR(perm, n);
}





int findI_reverse(int arr[], int n) {

    for (int i = n - 2; i >= 0; i--)
        if (arr[i] > arr[i + 1])
            return i;

    return -1;
}

int findJ_reverse(int arr[], int n, int I) {

    for (int j = n - 1; j > I; j--)
        if (arr[j] < arr[I])
            return j;

    return -1;
}

bool prev_permutation_narayana(int arr[], int n) {

    if (n < 2)
        return false;

    int I = findI_reverse(arr, n);

    if (I == -1)
        return false;

    int J = findJ_reverse(arr, n, I);

    if (J == -1)
        return false;

    swap(&arr[I], &arr[J]);

    reverseTail(arr, I + 1, n - 1);

    return true;
}

void permutations_reverse_narayana(int arr[], int n,
                                   void (*callback)(int perm[], int n)) {
    if (!callback)
        return;

    if (n == 0) {
        callback(arr, 0);
        return;
    }

    int *work = (int*)malloc(n * sizeof(int));
    if (!work)
        return;

    copyARR(arr, work, n);

    // начинаем с максимальной перестановки
    bubble_sort(work, n);
    reverseTail(work, 0, n - 1);

    callback(work, n);

    while (prev_permutation_narayana(work, n))
        callback(work, n);

    free(work);
}


