#include "permutations.h"


// ============================================================================
// Задача 2.1 Алгоритм Нарайаны
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

    return -1;
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

bool next_permutation_narayana(int arr[], int n) {
    int I = findI(arr, n);

    if (I == -1)
        return false;
    
    int J = findJ(arr, n, I);

    swap(&arr[I], &arr[J]);
    reverseTail(arr, I + 1, n - 1);

    
    return true;           
}

void print_callback(int perm[], int n) {
    printARR(perm, n);
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

// ============================================================================
// Задача 2.2
// ============================================================================

//вычисление факториала
long factorial(int n) {
    long result = 1;
    for (int i = 2; i <= n; i++) 
        result *= i;
    
    return result;
}

//преобразование индекса в факториальные цифры
void index_to_factorial_digits(long index, int n, int factorial_digits[]) {
    long temp = index;
    
    // Получаем факториальные цифры методом последовательного деления
    for (int i = 1; i <= n; i++) {
        factorial_digits[n - i] = temp % i;
        temp = temp / i;
    }
}

//получение перестановки по факториальным цифрам (алгоритм Лемера)
void lehmer_to_permutation(int arr[], int n, int factorial_digits[], int result[]) {
    // Создаем список доступных элементов [0, 1, 2, ..., n-1]
    int *available = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) 
        available[i] = i;
    
    
    // Строим перестановку по факториальным цифрам
    for (int i = 0; i < n; i++) {
        // Берём элемент на позиции factorial_digits[i]
        int pos = factorial_digits[i];
        int element_index = available[pos];
        
        // Копируем соответствующий элемент из исходного массива
        result[i] = arr[element_index];
        
        // Удаляем использованный индекс из списка доступных
        for (int j = pos; j < n - i - 1; j++) 
            available[j] = available[j + 1];
        
    }
    
    free(available);
}

//прямая генерация перестановки по индексу (ЗАДАЧА 2.2)
void permutation_from_index(int arr[], int n, long index, int result[]) {
    // 1. Проверка границ индекса
    long total_permutations = factorial(n);
    
    if (index < 0 || index >= total_permutations) {
        printf("Ошибка: индекс %ld вне диапазона [0, %ld)\n", index, total_permutations);
        // Можно вернуть исходный массив или первую перестановку
        copyARR(arr, result, n);
        bubble_sort(result, n);
        return;
    }
    
    // 2. Преобразование index в факториальные цифры
    int *factorial_digits = (int*)malloc(n * sizeof(int));
    index_to_factorial_digits(index, n, factorial_digits);
    
    // 3. Построение перестановки по факториальным цифрам
    lehmer_to_permutation(arr, n, factorial_digits, result);
    
    free(factorial_digits);
}

// генерация всех перестановок через факториальную систему
void permutations_factorial_system(int arr[], int n,
                                  void (*callback)(int perm[], int n)) {
    if (n <= 0 || !callback) 
        return;
    
    
    // 1. Вычисление n!
    long total = factorial(n);
    
    // 2. Создаем буфер для перестановки
    int *permutation = (int*)malloc(n * sizeof(int));
    if (permutation == NULL) 
        return;
    
    
    // 3. Цикл по всем индексам от 0 до n!-1
    for (long index = 0; index < total; index++) {
        // 4. Получаем перестановку по индексу
        permutation_from_index(arr, n, index, permutation);
        
        // 5. Вызываем callback с полученной перестановкой
        callback(permutation, n);
    }
    
    free(permutation);
}