#include "permutations.h"

// ============================================================================
// ЗАДАЧА 2.4: Алгоритм "Плюс-один" (инкрементальный)
// ============================================================================

// Преобразование массива индексов в перестановку
void indices_to_permutation(int arr[], int n, int indices[], int result[]) {
    // Просто копируем элементы по индексам
    for (int i = 0; i < n; i++) {
        result[i] = arr[indices[i]];
    }
}

// Инкремент массива индексов в смешанной системе счисления
bool increment_indices(int indices[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        // Ищем позицию для увеличения
        bool can_increment = false;
        for (int j = i + 1; j < n; j++) {
            if (indices[i] < indices[j]) {
                can_increment = true;
                break;
            }
        }
        
        if (can_increment) {
            indices[i]++;
            // Находим минимальное возможное значение для остальных позиций
            for (int j = i + 1; j < n; j++) {
                int min_val = 0;
                // Находим минимальное доступное значение
                bool used[256] = {false}; // Предполагаем n <= 256
                for (int k = 0; k < j; k++) {
                    if (indices[k] < n) {
                        used[indices[k]] = true;
                    }
                }
                
                while (min_val < n && used[min_val]) {
                    min_val++;
                }
                
                indices[j] = min_val;
            }
            return true;
        }
    }
    return false; // Все комбинации исчерпаны
}

void permutations_plus_one(int arr[], int n,
                          void (*callback)(int perm[], int n)) {
    // Проверка входных параметров
    if (n <= 0 || callback == NULL) return;
    
    // Инициализация массива индексов [0,1,2,...,n-1]
    int *indices = (int*)malloc(n * sizeof(int));
    int *current_perm = (int*)malloc(n * sizeof(int));
    
    if (indices == NULL || current_perm == NULL) {
        free(indices);
        free(current_perm);
        return;
    }
    
    // Создаем отсортированную копию массива
    int *sorted_arr = (int*)malloc(n * sizeof(int));
    if (sorted_arr == NULL) {
        free(indices);
        free(current_perm);
        return;
    }
    
    copyARR(arr, sorted_arr, n);
    bubble_sort(sorted_arr, n);
    
    // Начальная инициализация индексов
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }
    
    // Генерация всех перестановок
    do {
        // Преобразование индексов в перестановку исходного массива
        indices_to_permutation(sorted_arr, n, indices, current_perm);
        
        // Вызов callback() для каждой перестановки
        callback(current_perm, n);
        
    } while (increment_indices(indices, n));
    
    free(indices);
    free(current_perm);
    free(sorted_arr);
}