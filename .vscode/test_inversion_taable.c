
#include "permutations.h"


void test_inversion_functions() {

    printf("==============================================\n");
    printf("Тестирование алгоритма через таблицу инверсий\n");
    printf("==============================================\n");

    // ============================================================
    printf("\nТест 1: factorial_int(5) -> 120\n");
    long f = factorial(5);
    printf("Получили: %ld\n", f);
    printf("Ожидали: 120\n");
    assert(f == 120);
    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 2: is_valid_inversion_table\n");

    int valid[] = {0,1,0};
    int invalid[] = {0,5,0};

    bool r1 = is_valid_inversion_table(valid,3);
    bool r2 = is_valid_inversion_table(invalid,3);

    printf("Ожидали: true, false\n");
    printf("Получили: %s, %s\n",
           r1 ? "true" : "false",
           r2 ? "true" : "false");

    assert(r1 == true);
    assert(r2 == false);

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 3: index_to_inversion_table(3, n=3)\n");

    int inv[3];
    index_to_inversion_table(3,inv,3);

    printf("Полученная таблица инверсий: ");
    printARR(inv,3);

    printf("Проверяем диапазоны значений\n");

    assert(inv[0] >= 0 && inv[0] < 3);
    assert(inv[1] >= 0 && inv[1] < 2);
    assert(inv[2] >= 0 && inv[2] < 1);

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 4: permutation_from_inversion_table\n");

    int sorted[] = {1,2,3};
    int inv_zero[] = {0,0,0};
    int result[3];
    int expected[] = {1,2,3};

    printf("sorted: ");
    printARR(sorted,3);

    printf("inv: ");
    printARR(inv_zero,3);

    permutation_from_inversion_table(
        inv_zero,
        sorted,
        3,
        result);

    printf("Получили перестановку: ");
    printARR(result,3);

    printf("Ожидали: ");
    printARR(expected,3);

    for (int i = 0; i < 3; i++)
        assert(result[i] == expected[i]);

    printf("✓ Пройден\n");


    // ============================================================
    printf("\nТест 5: permutations_inversion_table [1,2,3]\n");
    printf("Ожидали все 6 перестановок:\n");
    printf("1 2 3\n");
    printf("1 3 2\n");
    printf("2 1 3\n");
    printf("2 3 1\n");
    printf("3 1 2\n");
    printf("3 2 1\n\n");

    int arr[] = {1,2,3};

    printf("Получили:\n");
    permutations_inversion_table(arr,3,print_callback);

    printf("✓ Визуально проверено\n");


    printf("\n==============================================\n");
    printf("Все тесты завершены успешно!\n");
    printf("==============================================\n");
}

int main() {
    test_inversion_functions();
    return 0;
}
