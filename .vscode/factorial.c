#include "permutations.h"


// ============================================================================
// Задача 2.2: Факториальная система счисления 
// ============================================================================

long factorial(int n) {
    long result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;
    return result;
}

// Индекс → факториальные цифры
void index_to_factorial_digits(long index, int n, int digits[]) {
    for (int i = 1; i <= n; i++) {
        digits[n - i] = index % i;
        index /= i;
    }
}

// Построение перестановки по коду Лемера
void lehmer_to_permutation(int arr[], int n, int digits[], int result[]) {
    int *available = (int*)malloc(n * sizeof(int));
    if (!available)
        return;

    for (int i = 0; i < n; i++)
        available[i] = i;

    for (int i = 0; i < n; i++) {
        int pos = digits[i];
        result[i] = arr[available[pos]];

        // удаляем использованный элемент
        for (int j = pos; j < n - i - 1; j++)
            available[j] = available[j + 1];
    }

    free(available);
}

// Прямой доступ к перестановке по номеру
bool permutation_from_index(int arr[], int n, long index, int result[]) {
    long total = factorial(n);

    if (index < 0 || index >= total)
        return false;

    int *digits = (int*)malloc(n * sizeof(int));
    if (!digits) return false;

    index_to_factorial_digits(index, n, digits);
    lehmer_to_permutation(arr, n, digits, result);

    free(digits);
    return true;
}

// Генерация всех перестановок
void permutations_factorial_system(int arr[], int n,
                                  void (*callback)(int perm[], int n)) {
    if (n <= 0 || !callback)
        return;

    // работаем с отсортированной копией
    int *work = (int*)malloc(n * sizeof(int));
    if (!work)
        return;

    copyARR(arr, work, n);
    bubble_sort(work, n);

    long total = factorial(n);
    int *perm = (int*)malloc(n * sizeof(int));
    if (!perm)
        return;

    for (long i = 0; i < total; i++) 
        if (permutation_from_index(work, n, i, perm))
            callback(perm, n);
    

    free(perm);
    free(work);
}
