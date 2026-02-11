#include "permutations.h"

/* ================= Вспомогательные ================= */

typedef struct {
    int **data;
    int count;
    int n;
} TestStorage;

TestStorage *current_storage = NULL;

void print_arr(int arr[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("]");
}

/* Callback для сбора перестановок */
void collect_callback(int perm[], int n) {
    int idx = current_storage->count;
    for (int i = 0; i < n; i++)
        current_storage->data[idx][i] = perm[i];
    current_storage->count++;
}

/* ================= ТЕСТЫ factorial ================= */

void test_factorial() {
    printf("Test factorial\n");

    printf("factorial(1) = %ld, ожидалось 1\n", factorial(1));
    printf("factorial(3) = %ld, ожидалось 6\n", factorial(3));
    printf("factorial(5) = %ld, ожидалось 120\n", factorial(5));

    assert(factorial(1) == 1);
    assert(factorial(3) == 6);
    assert(factorial(5) == 120);

    printf("OK\n\n");
}

/* ================= ТЕСТЫ permutation_from_index ================= */

void test_permutation_from_index_n3() {
    printf("Test permutation_from_index: n = 3\n");

    int arr[] = {1, 2, 3};
    int result[3];

    int expected[6][3] = {
        {1, 2, 3},
        {1, 3, 2},
        {2, 1, 3},
        {2, 3, 1},
        {3, 1, 2},
        {3, 2, 1}
    };

    for (int i = 0; i < 6; i++) {
        bool ok = permutation_from_index(arr, 3, i, result);
        assert(ok == true);

        printf("index = %d, получено: ", i);
        print_arr(result, 3);
        printf(" ожидалось: ");
        print_arr(expected[i], 3);
        printf("\n");

        for (int j = 0; j < 3; j++)
            assert(result[j] == expected[i][j]);
    }

    printf("OK\n\n");
}

void test_permutation_from_index_invalid() {
    printf("Test permutation_from_index: некорректный индекс\n");

    int arr[] = {1, 2, 3};
    int result[3];

    bool ok = permutation_from_index(arr, 3, 10, result);

    printf("index = 10, функция вернула: %s\n", ok ? "true" : "false");
    printf("ожидалось: false\n");

    assert(ok == false);

    printf("OK\n\n");
}

/* ================= ТЕСТЫ permutations_factorial_system ================= */

void test_permutations_factorial_n2() {
    printf("Test permutations_factorial_system: n = 2\n");

    int arr[] = {2, 1};

    TestStorage storage;
    storage.n = 2;
    storage.count = 0;
    storage.data = malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++)
        storage.data[i] = malloc(2 * sizeof(int));

    current_storage = &storage;
    permutations_factorial_system(arr, 2, collect_callback);

    int expected[2][2] = {
        {1, 2},
        {2, 1}
    };

    printf("Получено:\n");
    for (int i = 0; i < storage.count; i++) {
        print_arr(storage.data[i], 2);
        printf("\n");
    }

    printf("Ожидалось:\n");
    for (int i = 0; i < 2; i++) {
        print_arr(expected[i], 2);
        printf("\n");
    }

    assert(storage.count == 2);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            assert(storage.data[i][j] == expected[i][j]);

    for (int i = 0; i < 2; i++)
        free(storage.data[i]);
    free(storage.data);

    printf("OK\n\n");
}

void test_permutations_factorial_n3() {
    printf("Test permutations_factorial_system: n = 3\n");

    int arr[] = {3, 1, 2};

    TestStorage storage;
    storage.n = 3;
    storage.count = 0;
    storage.data = malloc(6 * sizeof(int*));
    for (int i = 0; i < 6; i++)
        storage.data[i] = malloc(3 * sizeof(int));

    current_storage = &storage;
    permutations_factorial_system(arr, 3, collect_callback);

    int expected[6][3] = {
        {1, 2, 3},
        {1, 3, 2},
        {2, 1, 3},
        {2, 3, 1},
        {3, 1, 2},
        {3, 2, 1}
    };

    printf("Получено:\n");
    for (int i = 0; i < storage.count; i++) {
        print_arr(storage.data[i], 3);
        printf("\n");
    }

    printf("Ожидалось:\n");
    for (int i = 0; i < 6; i++) {
        print_arr(expected[i], 3);
        printf("\n");
    }

    assert(storage.count == 6);
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            assert(storage.data[i][j] == expected[i][j]);

    for (int i = 0; i < 6; i++)
        free(storage.data[i]);
    free(storage.data);

    printf("OK\n\n");
}

void test_permutations_factorial_n0() {
    printf("Test permutations_factorial_system: n = 0\n");

    int arr[] = {};

    TestStorage storage;
    storage.n = 0;
    storage.count = 0;
    storage.data = NULL;

    current_storage = &storage;
    permutations_factorial_system(arr, 0, collect_callback);

    printf("Получено перестановок: %d\n", storage.count);
    printf("Ожидалось: 0\n");

    assert(storage.count == 0);

    printf("OK\n\n");
}

/* ================= MAIN ================= */

int main() {
    printf("=== UNIT TESTS FOR FACTORIAL SYSTEM ===\n\n");

    test_factorial();
    test_permutation_from_index_n3();
    test_permutation_from_index_invalid();
    test_permutations_factorial_n2();
    test_permutations_factorial_n3();
    test_permutations_factorial_n0();

    printf("=== ALL TESTS PASSED SUCCESSFULLY ===\n");
    return 0;
}
