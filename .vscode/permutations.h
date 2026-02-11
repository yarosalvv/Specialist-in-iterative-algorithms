#ifndef STUDENT2_H
#define STUDENT2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


// Вспомогательные функции
void bubble_sort(int arr[], int size);
void swap(int *a, int *b);
void reverseTail(int arr[], int start, int end);
void copyARR(int arr[], int copy[], int n);
void printARR(int arr[], int n);

// Вспомогательные функции алгоритма Нарайаны
int findI(int arr[], int n);
int findJ(int arr[], int n, int I);

// Callback для примеров / тестов
void print_callback(int perm[], int n);

// Основной алгоритм Нарайаны
bool next_permutation_narayana(int arr[], int n);
void permutation_narayana(int arr[], int n,
                           void (*callback)(int perm[], int n));



                           
long factorial(int n);
void index_to_factorial_digits(long index, int n, int factorial_digits[]);

#endif

