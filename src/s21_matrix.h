#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include "stdio.h"
#include "stdlib.h"

#define EPS 1e-7

// для функций сравнения
#define SUCCESS 0
#define FAILURE 1

// Все операции (кроме сравнения матриц)
#define OK 0
#define ERROR_INVALID_MATRIX 1
#define ERROR_CALCULATION 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// пользовательские функции
void set_matrix(matrix_t *A, double in_matrix[][10]);
int size_compare(matrix_t *A, matrix_t *B);

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);

// int s21_determinant(matrix_t *A, double *result);

// int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_