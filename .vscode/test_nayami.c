
#include "permutations.h"

void test_next_permutation() {
    printf("=== Тестирование next_permutation_narayana ===\n\n");
    
    // Тест 1: [1, 2, 4, 3] -> [1, 3, 2, 4]
    printf("Тест 1: [1, 2, 4, 3] -> [1, 3, 2, 4]\n");
    printf("Исходный массив: ");
    int arr1[] = {1, 2, 4, 3};
    printARR(arr1, 4);
    
    int expected1[] = {1, 3, 2, 4};
    bool has_next = next_permutation_narayana(arr1, 4);
    
    printf("Результат функции: %s\n", has_next ? "true" : "false");
    printf("Полученный массив: ");
    printARR(arr1, 4);
    
    assert(has_next == true);
    for (int i = 0; i < 4; i++) {
        assert(arr1[i] == expected1[i]);
    }
    printf("✓ Пройден\n");
    
    // Тест 2: [3, 1, 4, 2] -> [3, 2, 1, 4]
    printf("\nТест 2: [3, 1, 4, 2] -> [3, 2, 1, 4]\n");
    printf("Исходный массив: ");
    int arr2[] = {3, 1, 4, 2};
    printARR(arr2, 4);
    
    int expected2[] = {3, 2, 1, 4};
    has_next = next_permutation_narayana(arr2, 4);
    
    printf("Результат функции: %s\n", has_next ? "true" : "false");
    printf("Полученный массив: ");
    printARR(arr2, 4);
    
    assert(has_next == true);
    for (int i = 0; i < 4; i++) {
        assert(arr2[i] == expected2[i]);
    }
    printf("✓ Пройден\n");
    
    // Тест 3: [4, 3, 2, 1] -> последняя перестановка (false)
    printf("\nТест 3: [4, 3, 2, 1] -> последняя перестановка (должен вернуть false)\n");
    printf("Исходный массив: ");
    int arr3[] = {4, 3, 2, 1};
    printARR(arr3, 4);
    
    int original3[] = {4, 3, 2, 1}; // Сохраняем оригинал для проверки
    has_next = next_permutation_narayana(arr3, 4);
    
    printf("Результат функции: %s\n", has_next ? "true" : "false");
    printf("Полученный массив: ");
    printARR(arr3, 4);
    
    assert(has_next == false);
    // Проверяем, что массив не изменился
    for (int i = 0; i < 4; i++) {
        assert(arr3[i] == original3[i]);
    }
    printf("✓ Пройден\n");
    
    // Тест 4: Все перестановки [1, 2, 3] (должно быть 3! = 6 перестановок)
    printf("\nТест 4: Все перестановки [1, 2, 3] (должно быть 6 перестановок)\n");
    int arr4[] = {1, 2, 3};
    int all_permutations[6][3] = {
        {1, 2, 3},
        {1, 3, 2},
        {2, 1, 3},
        {2, 3, 1},
        {3, 1, 2},
        {3, 2, 1}
    };
    
    // Проверяем начальную перестановку
    printf("Начальная перестановка: ");
    printARR(arr4, 3);
    for (int i = 0; i < 3; i++) {
        assert(arr4[i] == all_permutations[0][i]);
    }
    
    // Генерируем и проверяем остальные 5 перестановок
    int count = 0;
    while (next_permutation_narayana(arr4, 3)) {
        count++;
        printf("Вызов %d, результат функции: true\n", count);
        printf("Перестановка %d: ", count + 1);
        printARR(arr4, 3);
        
        // Проверяем, что текущая перестановка соответствует ожидаемой
        for (int i = 0; i < 3; i++) {
            assert(arr4[i] == all_permutations[count][i]);
        }
    }
    
    // Проверяем последний вызов (должен вернуть false)
    printf("Вызов %d, результат функции: false (перестановки закончились)\n", count + 1);
    
    // Мы должны получить 5 успешных вызовов next_permutation
    assert(count == 5);
    printf("Всего успешных вызовов next_permutation: %d\n", count);
    printf("✓ Пройден (получено %d перестановок, всего 6 с начальной)\n", count + 1);
    
    // Тест 5: Дополнительная проверка - после последней перестановки должен вернуться false
    printf("\nТест 5: Проверка, что после всех перестановок возвращается false\n");
    printf("Текущий массив: ");
    printARR(arr4, 3);
    has_next = next_permutation_narayana(arr4, 3);
    printf("Результат функции: %s\n", has_next ? "true" : "false");
    assert(has_next == false);
    printf("✓ Пройден\n");
    
    // Тест 6: Одна перестановка для массива из одного элемента
    printf("\nТест 6: Массив из одного элемента [5]\n");
    printf("Исходный массив: ");
    int arr6[] = {5};
    printARR(arr6, 1);
    
    has_next = next_permutation_narayana(arr6, 1);
    printf("Результат функции: %s\n", has_next ? "true" : "false");
    printf("Полученный массив: ");
    printARR(arr6, 1);
    
    assert(has_next == false); // Для одного элемента должна быть только одна перестановка
    assert(arr6[0] == 5); // Массив не должен измениться
    printf("✓ Пройден\n");
    
    // Тест 7: Пустой массив
    printf("\nТест 7: Пустой массив (n=0)\n");
    printf("Пустой массив, n=0\n");
    int arr7[] = {}; // Пустой массив
    has_next = next_permutation_narayana(arr7, 0);
    printf("Результат функции: %s\n", has_next ? "true" : "false");
    assert(has_next == false); // Для пустого массива должна возвращать false
    printf("✓ Пройден\n");
    
    // Тест 8: Дополнительный тест с массивом [2, 1, 3]
    printf("\nТест 8: Дополнительный тест [2, 1, 3]\n");
    printf("Исходный массив: ");
    int arr8[] = {2, 1, 3};
    printARR(arr8, 3);
    
    has_next = next_permutation_narayana(arr8, 3);
    printf("Результат функции: %s\n", has_next ? "true" : "false");
    printf("Полученный массив: ");
    printARR(arr8, 3);
    
    // [2, 1, 3] -> [2, 3, 1]
    int expected8[] = {2, 3, 1};
    assert(has_next == true);
    for (int i = 0; i < 3; i++) {
        assert(arr8[i] == expected8[i]);
    }
    printf("✓ Пройден\n");
    
    printf("\n==============================================\n");
    printf("Все тесты пройдены успешно!\n");
    printf("==============================================\n");
}

int main() {
    test_next_permutation();
    return 0;
}