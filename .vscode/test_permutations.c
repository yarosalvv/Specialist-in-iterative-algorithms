#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// ============================================================================
// Вспомогательные функции для тестирования
// ============================================================================

int total_calls = 0;

void counting_callback(int perm[], int n) {
    total_calls++;
    printf("%3d: ", total_calls);
    print_array(perm, n);
    printf("\n");
}

void test_algorithm(const char* name, 
                   void (*algo)(int[], int, void(*)(int[], int)),
                   int arr[], int n) {
    printf("\n=== Тестирование алгоритма: %s ===\n", name);
    printf("Исходный массив: ");
    print_array(arr, n);
    printf("\n");
    
    total_calls = 0;
    algo(arr, n, counting_callback);
    
    long long expected = factorial(n);
    printf("Всего перестановок: %d (ожидалось: %lld)\n", 
           total_calls, expected);
    assert(total_calls == expected);
}

// ============================================================================
// Основные тесты
// ============================================================================

void test_narayana() {
    printf("\n=== Тест алгоритма Нарайаны ===\n");
    
    int arr1[] = {1, 2, 3};
    int n1 = 3;
    
    printf("Тест 1: Перестановки [1, 2, 3]\n");
    int perm[3];
    array_copy(arr1, perm, n1);
    
    int count = 1;
    printf("%d: ", count);
    print_array(perm, n1);
    printf("\n");
    
    while (next_permutation_narayana(perm, n1)) {
        count++;
        printf("%d: ", count);
        print_array(perm, n1);
        printf("\n");
    }
    assert(count == 6);
    
    // Тест prev_permutation
    printf("\nТест prev_permutation (обратный порядок):\n");
    array_copy(arr1, perm, n1);
    // Сначала получаем последнюю перестановку
    while (next_permutation_narayana(perm, n1)) {}
    
    count = 6;
    while (prev_permutation_narayana(perm, n1)) {
        count--;
        printf("%d: ", count);
        print_array(perm, n1);
        printf("\n");
    }
    assert(count == 1);
}

void test_factorial_system() {
    printf("\n=== Тест факториальной системы ===\n");
    
    int arr[] = {1, 2, 3, 4};
    int n = 4;
    int result[4];
    
    printf("Прямой доступ к перестановкам по индексу:\n");
    for (int i = 0; i < 24; i++) {
        permutation_from_index(arr, n, i, result);
        printf("Индекс %2d: ", i);
        print_array(result, n);
        printf("\n");
    }
    
    // Проверка краевых случаев
    printf("\nПроверка индексов вне диапазона:\n");
    permutation_from_index(arr, n, -1, result);
    printf("Индекс -1: ");
    print_array(result, n);
    printf(" (должна быть первая перестановка)\n");
    
    permutation_from_index(arr, n, 100, result);
    printf("Индекс 100: ");
    print_array(result, n);
    printf(" (должна быть первая перестановка)\n");
}

void test_inversion_table() {
    printf("\n=== Тест таблицы инверсий ===\n");
    
    int perm[] = {3, 1, 4, 2};
    int n = 4;
    int inv_table[4];
    int restored[4];
    
    inversion_table_from_permutation(perm, n, inv_table);
    printf("Перестановка: ");
    print_array(perm, n);
    printf("\nТаблица инверсий: ");
    print_array(inv_table, n);
    printf("\n");
    
    permutation_from_inversion_table(inv_table, n, restored);
    printf("Восстановленная: ");
    print_array(restored, n);
    printf("\n");
    
    assert(array_compare(perm, restored, n) == 0);
}

void test_comprehensive() {
    printf("\n=== Комплексное тестирование всех алгоритмов ===\n");
    
    int arr[] = {1, 2, 3};
    int n = 3;
    
    test_algorithm("Алгоритм Нарайаны", permutations_narayana, arr, n);
    test_algorithm("Факториальная система", permutations_factorial_system, arr, n);
    test_algorithm("Таблица инверсий", permutations_inversion_table, arr, n);
    test_algorithm("Алгоритм Плюс-один", permutations_plus_one, arr, n);
    test_algorithm("Обратный Нарайана", permutations_reverse_narayana, arr, n);
}

void test_edge_cases() {
    printf("\n=== Тестирование граничных случаев ===\n");
    
    // Пустой массив
    printf("Тест с n=0:\n");
    permutations_narayana(NULL, 0, counting_callback);
    printf("Кол-во вызовов: %d\n", total_calls);
    
    // Массив из одного элемента
    int arr1[] = {42};
    printf("\nТест с n=1 [42]:\n");
    total_calls = 0;
    permutations_narayana(arr1, 1, counting_callback);
    assert(total_calls == 1);
    
    // Массив из двух элементов
    int arr2[] = {2, 1};
    printf("\nТест с n=2 [2, 1]:\n");
    total_calls = 0;
    permutations_narayana(arr2, 2, counting_callback);
    assert(total_calls == 2);
}

int main() {
    printf("=== Начало тестирования алгоритмов перестановок ===\n");
    
    test_narayana();
    test_factorial_system();
    test_inversion_table();
    test_comprehensive();
    test_edge_cases();
    
    printf("\n=== Все тесты пройдены успешно! ===\n");
    return 0;
}