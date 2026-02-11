
#include "permutations.h"

int arrays_equal(int a[], int b[], int n) {
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

void test_plus_one_algorithm() {

    printf("==============================================\n");
    printf("Тестирование алгоритма Плюс-один\n");
    printf("==============================================\n");

    // ============================================================
    printf("\nТест 1: build_permutation_from_indices\n");

    int sorted1[]  = {1,2,3};
    int indices1[] = {0,0,0};
    int result1[3];
    int temp1[3];
    int expected1[] = {1,2,3};

    printf("sorted: ");
    printARR(sorted1,3);

    printf("indices: ");
    printARR(indices1,3);

    build_permutation_from_indices(
        sorted1,
        indices1,
        3,
        result1,
        temp1);

    printf("Получили: ");
    printARR(result1,3);

    printf("Ожидали: ");
    printARR(expected1,3);

    assert(arrays_equal(result1,expected1,3));

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 2: increment_factoradic\n");

    int indices2[] = {0,0,0};

    printf("Исходные индексы: ");
    printARR(indices2,3);

    increment_factoradic(indices2,3);

    printf("После increment: ");
    printARR(indices2,3);

    int expected2[] = {0,1,0};

    printf("Ожидали: ");
    printARR(expected2,3);

    assert(arrays_equal(indices2,expected2,3));

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 3: build_permutation_from_indices сложный случай\n");

    int sorted3[]  = {1,2,3};
    int indices3[] = {1,0,0};
    int result3[3];
    int temp3[3];
    int expected3[] = {2,1,3};

    printf("sorted: ");
    printARR(sorted3,3);

    printf("indices: ");
    printARR(indices3,3);

    build_permutation_from_indices(
        sorted3,
        indices3,
        3,
        result3,
        temp3);

    printf("Получили: ");
    printARR(result3,3);

    printf("Ожидали: ");
    printARR(expected3,3);

    assert(arrays_equal(result3,expected3,3));

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 4: permutations_plus_one [1,2,3]\n");

    int arr4[] = {1,2,3};

    printf("Ожидали перестановки:\n");
    printf("1 2 3\n");
    printf("1 3 2\n");
    printf("2 1 3\n");
    printf("2 3 1\n");
    printf("3 1 2\n");
    printf("3 2 1\n");

    printf("\nПолучили:\n");

    permutations_plus_one(arr4,3,print_callback);

    printf("✓ Визуально проверено\n");


    // ============================================================
    printf("\nТест 5: permutations_plus_one n=0\n");

    int arr5[] = {};

    printf("Пустой массив, ожидаем один callback\n");

    permutations_plus_one(arr5,0,print_callback);

    printf("✓ Пройден\n");


    printf("\n==============================================\n");
    printf("Все тесты завершены успешно!\n");
    printf("==============================================\n");
}

int main() {
    test_plus_one_algorithm();
    return 0;
}