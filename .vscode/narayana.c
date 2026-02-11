#include "permutations.h"

// ============================================================================
// Задача 2.1 Алгоритм Нарайаны
// ============================================================================


void printARR(int arr[], int n){

    for (int h = 0; h < n; h++) 
        printf("%d ", arr[h]);

    printf("\n");
}

void print_callback(int perm[], int n) {
    printARR(perm, n);
}

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

int findI(int arr[], int n) {

    for (int i = n-2; i >= 0; i--)
        if (arr[i] < arr[i+1])
            return i;
    
    return -1;
}

int findJ(int arr[], int n, int I) {

    for (int j = n - 1; j > I; j--)
        if (arr[j] > arr[I])
            return j;
}

void reverseTail(int arr[], int start, int end) {
    // Разворачиваем часть массива от start до end
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}


void copyARR(int arr[], int copy[], int n){
    for (int i = 0; i < n; i++)
        copy[i] = arr[i];
}

bool next_permutation_narayana(int arr[], int n) {
    if (n < 2) 
        return false;
        
    int I = findI(arr, n);

    if (I == -1)
        return false;
    
    int J = findJ(arr, n, I);

    swap(&arr[I], &arr[J]);
    reverseTail(arr, I + 1, n - 1);

    
    return true;           
}

void permutation_narayana(int arr[],int n, 
                            void (*callback)(int perm[], int n)){
    if (n <= 0 || !callback)
        return;
    
    // Создаем рабочую копию и сортируем ее
    int *work = (int*)malloc(n * sizeof(int));
    if (work == NULL)
        return;
    
    copyARR(arr, work, n);
    bubble_sort(work, n);

    // Вызываем callback для первой перестановки
    callback(work, n);

    // Генерируем все остальные перестановки
    while (next_permutation_narayana(work, n)) 
        callback(work, n);
    
    free(work);
}
