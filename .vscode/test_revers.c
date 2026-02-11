
#include "permutations.h"

int arrays_equal(int a[], int b[], int n) {
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

void test_reverse_narayana() {

    printf("==============================================\n");
    printf("Тестирование Reverse Narayana\n");
    printf("==============================================\n");


    // ============================================================
    printf("\nТест 1: prev_permutation_narayana [3,2,1] -> [3,1,2]\n");

    int arr1[] = {3,2,1};
    int expected1[] = {3,1,2};

    printf("Исходный массив: ");
    printARR(arr1,3);

    bool res = prev_permutation_narayana(arr1,3);

    printf("Результат функции: %s\n", res ? "true":"false");
    printf("Получили: ");
    printARR(arr1,3);

    printf("Ожидали: ");
    printARR(expected1,3);

    assert(res == true);
    assert(arrays_equal(arr1,expected1,3));

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 2: prev_permutation_narayana минимальная перестановка\n");

    int arr2[] = {1,2,3};
    int original2[] = {1,2,3};

    printf("Исходный массив: ");
    printARR(arr2,3);

    res = prev_permutation_narayana(arr2,3);

    printf("Результат функции: %s\n", res ? "true":"false");
    printf("Получили: ");
    printARR(arr2,3);

    assert(res == false);
    assert(arrays_equal(arr2,original2,3));

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 3: массив из одного элемента\n");

    int arr3[] = {5};

    printf("Исходный массив: ");
    printARR(arr3,1);

    res = prev_permutation_narayana(arr3,1);

    printf("Результат функции: %s\n", res ? "true":"false");

    assert(res == false);
    assert(arr3[0] == 5);

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 4: permutations_reverse_narayana [1,2,3]\n");

    int arr4[] = {1,2,3};

    printf("Ожидали порядок:\n");
    printf("3 2 1\n");
    printf("3 1 2\n");
    printf("2 3 1\n");
    printf("2 1 3\n");
    printf("1 3 2\n");
    printf("1 2 3\n");

    printf("\nПолучили:\n");

    permutations_reverse_narayana(arr4,3,print_callback);

    printf("✓ Визуально проверено\n");


    // ============================================================
    printf("\nТест 5: permutations_reverse_narayana n=0\n");

    int arr5[] = {};

    printf("Пустой массив — ожидаем один callback\n");

    permutations_reverse_narayana(arr5,0,print_callback);

    printf("✓ Пройден\n");


    printf("\n==============================================\n");
    printf("Все тесты пройдены успешно!\n");
    printf("==============================================\n");
}

int main() {
    test_reverse_narayana();
    return 0;
}
