#include "permutations.h"

// ============================================================================
// ЗАДАЧА 2.3: Алгоритм через таблицу инверсий
// ============================================================================

// Создание таблицы инверсий из перестановки
void inversion_table_from_permutation(int perm[], int n, int inv_table[]) {
    for (int i = 0; i < n; i++) {
        inv_table[i] = 0;
        for (int j = 0; j < i; j++) {
            if (perm[j] > perm[i]) {
                inv_table[i]++;
            }
        }
    }
}

// Проверка корректности таблицы инверсий
bool is_valid_inversion_table(int inv_table[], int n) {
    for (int i = 0; i < n; i++) {
        if (inv_table[i] < 0 || inv_table[i] > i) {
            return false;
        }
    }
    return true;
}

// Алгоритм построения перестановки по таблице инверсий (метод вставок)
void permutation_from_inversion_table(int inv_table[], int n, int result[]) {
    // Проверка корректности таблицы инверсий
    if (!is_valid_inversion_table(inv_table, n)) {
        // Возвращаем начальную перестановку при ошибке
        for (int i = 0; i < n; i++) {
            result[i] = i + 1;
        }
        return;
    }
    
    // Создаем список для эффективной вставки
    // Используем связанный список на массиве
    int *next = (int*)malloc((n + 1) * sizeof(int));
    if (next == NULL) return;
    
    // Инициализация списка: -1 означает конец списка
    for (int i = 0; i <= n; i++) {
        next[i] = -1;
    }
    
    // Строим перестановку, начиная с последнего элемента
    for (int i = n - 1; i >= 0; i--) {
        int pos = i; // Начальная позиция для вставки
        int count = inv_table[i]; // Количество пропусков
        
        // Находим нужную позицию для элемента i+1
        int current = 0; // Начинаем с головы списка
        int prev = -1;
        
        // Пропускаем count элементов
        while (count > 0 && next[current] != -1) {
            prev = current;
            current = next[current];
            count--;
        }
        
        // Вставляем элемент i+1
        if (prev == -1) {
            // Вставка в начало
            next[i + 1] = current;
            // Обновляем голову
            next[0] = i + 1;
        } else {
            // Вставка после prev
            next[i + 1] = next[prev];
            next[prev] = i + 1;
        }
    }
    
    // Преобразуем список в массив
    int idx = 0;
    int current = next[0];
    while (current != -1 && idx < n) {
        result[idx++] = current;
        current = next[current];
    }
    
    // Заполняем оставшиеся позиции
    while (idx < n) {
        result[idx++] = idx;
    }
    
    free(next);
}

// Генерация следующей таблицы инверсий
bool next_inversion_table(int inv_table[], int n) {
    // Инкрементируем таблицу инверсий как число в смешанной системе счисления
    // где каждая цифра i находится в диапазоне [0, i]
    
    for (int i = n - 1; i >= 0; i--) {
        if (inv_table[i] < i) {
            inv_table[i]++;
            // Сбрасываем все младшие цифры
            for (int j = i + 1; j < n; j++) {
                inv_table[j] = 0;
            }
            return true;
        }
    }
    return false; // Все таблицы сгенерированы
}

void permutations_inversion_table(int arr[], int n,
                                 void (*callback)(int perm[], int n)) {
    // Проверка входных параметров
    if (n <= 0 || callback == NULL) return;
    
    // Сортируем исходный массив для согласованности
    int *sorted_arr = (int*)malloc(n * sizeof(int));
    if (sorted_arr == NULL) return;
    
    copyARR(arr, sorted_arr, n);
    bubble_sort(sorted_arr, n);
    
    // Выделяем память для таблицы инверсий и перестановки
    int *inv_table = (int*)malloc(n * sizeof(int));
    int *current_perm = (int*)malloc(n * sizeof(int));
    if (inv_table == NULL || current_perm == NULL) {
        free(sorted_arr);
        free(inv_table);
        free(current_perm);
        return;
    }
    
    // Инициализация нулевой таблицы инверсий
    for (int i = 0; i < n; i++) {
        inv_table[i] = 0;
    }
    
    // Генерация всех возможных таблиц инверсий
    do {
        // Строим перестановку из отсортированного массива
        // Сначала получаем перестановку индексов
        int *index_perm = (int*)malloc(n * sizeof(int));
        if (index_perm == NULL) break;
        
        permutation_from_inversion_table(inv_table, n, index_perm);
        
        // Преобразуем перестановку индексов в перестановку исходного массива
        for (int i = 0; i < n; i++) {
            current_perm[i] = sorted_arr[index_perm[i] - 1]; // -1 т.к. индексы с 1
        }
        
        // Вызываем callback
        callback(current_perm, n);
        
        free(index_perm);
        
    } while (next_inversion_table(inv_table, n));
    
    free(sorted_arr);
    free(inv_table);
    free(current_perm);
}