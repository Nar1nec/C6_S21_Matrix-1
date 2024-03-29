/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "./s21_matrix.h" instead.
 */

#include <check.h>

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

// int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);
double calc_determinant(matrix_t *result);

// int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_
#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

START_TEST(cr1)
{
  matrix_t matrix;
  ck_assert_uint_eq(s21_create_matrix(3, 4, &matrix), 0);
  s21_remove_matrix(&matrix);

}
END_TEST

START_TEST(cr2)
{
  matrix_t matrix;
  ck_assert_uint_eq(s21_create_matrix(0, 4, &matrix), 1);

}
END_TEST

START_TEST(cr3)
{
  matrix_t matrix;
  ck_assert_uint_eq(s21_create_matrix(3, -2, &matrix), 1);

}
END_TEST

START_TEST(cr4)
{
  matrix_t matrix;
  ck_assert_uint_eq(s21_create_matrix(0, 0, &matrix), 1);
#include <check.h>
#include <stdlib.h>
#include <math.h>

#include "s21_matrix.h"

}
END_TEST

START_TEST(deter1)
{
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(5, 5, &matrix1), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5, 2, 8},
                            {3, 5, 6, -2, 0},
                            {13, 15, -6, 2, 9},
                            {1, 8, 7, 12, -23},
                            {6, 9, 1, 10, 0}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = 20006;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, EPS);

  s21_remove_matrix(&matrix1);

}
END_TEST

START_TEST(deter2)
{
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);

  double in_mat1[10][10] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = 0;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, EPS);

  s21_remove_matrix(&matrix1);

}
END_TEST

START_TEST(deter3)
{
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix1), 0);

  double in_mat1[10][10] = {{1, 2, 3}, {4, 5, 6}};

  set_matrix(&matrix1, in_mat1);

  double result;
  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 2);

  s21_remove_matrix(&matrix1);


}
END_TEST

START_TEST(deter4)
{
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(2, 2, &matrix1), 0);

  double in_mat1[10][10] = {{1, 2}, {4, 5}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = -3;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, EPS);

  s21_remove_matrix(&matrix1);


}
END_TEST

START_TEST(deter5)
{
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(1, 1, &matrix1), 0);

  double in_mat1[10][10] = {{666}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = 666;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, EPS);

  s21_remove_matrix(&matrix1);

}
END_TEST

START_TEST(deter6)
{
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(5, 5, &matrix1), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5, 2, 0},
                            {3, 0, 6, -2, 0},
                            {13, 15, -6, 0, 9},
                            {1, 0, 7, 12, -23},
                            {6, 9, 1, 0, 0}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = -33416;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, EPS);

  s21_remove_matrix(&matrix1);

}
END_TEST

START_TEST(deter7)
{
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(6, 6, &matrix1), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5, 2, 0, 8}, {3, 0, 6, -2, 0, 7},
                            {13, 15, -6, 0, 9, 5},    {1, 0, 7, 12, -23, 3},
                            {6, 9, 1, 0, 0, 2},       {4, 7, -3, -2, 4, 8}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = -344160;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, EPS);

  s21_remove_matrix(&matrix1);

}
END_TEST

START_TEST(deter8)
{
  matrix_t matrix1;
  ck_assert_uint_eq(s21_create_matrix(4, 4, &matrix1), 0);

  double in_mat1[10][10] = {
      {1, 2, 3, 4}, {4, 0, 0, 3}, {0, 3, 3, 1}, {0, 7, 2, 6}};

  set_matrix(&matrix1, in_mat1);

  double result;
  double etalon = 199;

  ck_assert_uint_eq(s21_determinant(&matrix1, &result), 0);
  ck_assert_float_eq_tol(result, etalon, EPS);

  s21_remove_matrix(&matrix1);
#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

}
END_TEST

START_TEST(eq0)
{
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix2), 0);

  double in_mat1[10][10] = {{1.5123456, 2.5, 4.5}, {4.5, 5.5, 8.5}};
  double in_mat2[10][10] = {{1.5123456, 2.5, 4.5}, {4.5, 5.5, 8.5}};
  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);


}
END_TEST

START_TEST(eq1)
{
    matrix_t matrix1, matrix2;
    ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix1), 0);
    ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix2), 0);

    double in_mat1[10][10] = {{1.5, 0.512344578, 4.5}, {4.5, 5.5, 8.5}};
    double in_mat2[10][10] = {{1.5, 0.512345578, 4.5}, {4.5, 5.5, 8.5}};
    set_matrix(&matrix1, in_mat1);
    set_matrix(&matrix2, in_mat2);

    ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
    s21_remove_matrix(&matrix1);
    s21_remove_matrix(&matrix2);

}
END_TEST

START_TEST(eq2)
{
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(2, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(1, 3, &matrix2), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {4.5, 5.5, 8.5}};
  double in_mat2[10][10] = {{1.5, 0.5, 4.5}};
  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);

}
END_TEST

START_TEST(eq3)
{
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(1, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 1, &matrix2), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}};
  double in_mat2[10][10] = {{1.5}, {0.5}, {4.5}};
  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);

}
END_TEST

START_TEST(eq4)
{
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(1, 1, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(1, 1, &matrix2), 0);

  double in_mat1[10][10] = {{1.5}};
  double in_mat2[10][10] = {{1.5}};
  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);

}
END_TEST

START_TEST(eq5)
{
  matrix_t matrix1, matrix2;
  ck_assert_uint_eq(s21_create_matrix(10, 15, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(10, 15, &matrix2), 0);

  ck_assert_uint_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

}
END_TEST

START_TEST(mult1)
{
  matrix_t matrix1, matrix2, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix2), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_mat2[10][10] = {{1.5, 4, 2}, {0.5, 3, 10}, {4.5, 3, 2}};
  double in_etalon[10][10] = {{23.75, 27, 37}, {34, 45, 68}, {47, 56, 92}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);


}
END_TEST

START_TEST(mult2)
{
  matrix_t matrix1, matrix2, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(5, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 2, &matrix2), 0);
  ck_assert_uint_eq(s21_create_matrix(5, 2, &etalon), 0);

  double in_mat1[10][10] = {
      {1.5, 2.5, 4.5}, {3, 5, 6}, {13, 15, -6}, {1, 8, 7}, {6, 9, 1}};
  double in_mat2[10][10] = {{1.5, 4}, {0.5, 3}, {4.5, 3}};
  double in_etalon[10][10] = {
      {23.75, 27}, {34, 45}, {0, 79}, {37, 49}, {18, 54}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);


}
END_TEST

START_TEST(mult3)
{
  matrix_t matrix1, matrix2, result;
  ck_assert_uint_eq(s21_create_matrix(5, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(2, 2, &matrix2), 0);

  double in_mat1[10][10] = {
      {1.5, 2.5, 4.5}, {3, 5, 6}, {13, 15, -6}, {1, 8, 7}, {6, 9, 1}};
  double in_mat2[10][10] = {{1.5, 4}, {0.5, 3}, {4.5, 3}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_mult_matrix(&matrix1, &matrix2, &result), 2);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

}
END_TEST

START_TEST(mn0)
{
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_etalon[10][10] = {{3.0, 5.0, 9.0}, {6, 10, 12}, {4, 14, 18}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_mult_number(&matrix1, 2, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);

}
END_TEST

START_TEST(mn1)
{
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_etalon[10][10] = {{0.0, 0.0, 0.0}, {0, 0, 0}, {0, 0, 0}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_mult_number(&matrix1, 0, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

}
END_TEST

START_TEST(sub0)
{
  matrix_t matrix1, matrix2, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix2), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_mat2[10][10] = {{1.5, 4, 2}, {0.5, 3, 10}, {4.5, 3, 2}};
  double in_etalon[10][10] = {{0.0, -1.5, 2.5}, {2.5, 2, -4}, {-2.5, 4, 7}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_sub_matrix(&matrix1, &matrix2, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);

}
END_TEST

START_TEST(sub1)
{
  matrix_t matrix1, matrix2, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 2, &matrix2), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_mat2[10][10] = {{1.5, 4, 2}, {0.5, 3, 10}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_sub_matrix(&matrix1, &matrix2, &result), 2);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"


}
END_TEST

START_TEST(sum0)
{
  matrix_t matrix1, matrix2, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix2), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 3, &etalon), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_mat2[10][10] = {{1.5, 4, 2}, {0.5, 3, 10}, {4.5, 3, 2}};
  double in_etalon[10][10] = {{3.0, 6.5, 6.5}, {3.5, 8, 16}, {6.5, 10, 11}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_sum_matrix(&matrix1, &matrix2, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);


}
END_TEST

START_TEST(sum1)
{
  matrix_t matrix1, matrix2, result;
  ck_assert_uint_eq(s21_create_matrix(3, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 2, &matrix2), 0);

  double in_mat1[10][10] = {{1.5, 2.5, 4.5}, {3, 5, 6}, {2, 7, 9}};
  double in_mat2[10][10] = {{1.5, 4, 2}, {0.5, 3, 10}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&matrix2, in_mat2);

  ck_assert_uint_eq(s21_sum_matrix(&matrix1, &matrix2, &result), 2);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

}
END_TEST

START_TEST(transp0)
{
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(5, 3, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(3, 5, &etalon), 0);

  double in_mat1[10][10] = {
      {1.5, 2.5, 4.5}, {3, 5, 6}, {13, 15, -6}, {1, 8, 7}, {6, 9, 1}};
  double in_etalon[10][10] = {
      {1.5, 3, 13, 1, 6}, {2.5, 5, 15, 8, 9}, {4.5, 6, -6, 7, 1}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_transpose(&matrix1, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);


}
END_TEST

START_TEST(transp1)
{
  matrix_t matrix1, etalon, result;
  ck_assert_uint_eq(s21_create_matrix(5, 1, &matrix1), 0);
  ck_assert_uint_eq(s21_create_matrix(1, 5, &etalon), 0);

  double in_mat1[10][10] = {{1.5}, {3}, {13}, {1}, {6}};
  double in_etalon[10][10] = {{1.5, 3, 13, 1, 6}};

  set_matrix(&matrix1, in_mat1);
  set_matrix(&etalon, in_etalon);

  ck_assert_uint_eq(s21_transpose(&matrix1, &result), 0);
  ck_assert_uint_eq(s21_eq_matrix(&result, &etalon), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&etalon);
  s21_remove_matrix(&result);
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, cr1);
    tcase_add_test(tc1_1, cr2);
    tcase_add_test(tc1_1, cr3);
    tcase_add_test(tc1_1, cr4);
    tcase_add_test(tc1_1, deter1);
    tcase_add_test(tc1_1, deter2);
    tcase_add_test(tc1_1, deter3);
    tcase_add_test(tc1_1, deter4);
    tcase_add_test(tc1_1, deter5);
    tcase_add_test(tc1_1, deter6);
    tcase_add_test(tc1_1, deter7);
    tcase_add_test(tc1_1, deter8);
    tcase_add_test(tc1_1, eq0);
    tcase_add_test(tc1_1, eq1);
    tcase_add_test(tc1_1, eq2);
    tcase_add_test(tc1_1, eq3);
    tcase_add_test(tc1_1, eq4);
    tcase_add_test(tc1_1, eq5);
    tcase_add_test(tc1_1, mult1);
    tcase_add_test(tc1_1, mult2);
    tcase_add_test(tc1_1, mult3);
    tcase_add_test(tc1_1, mn0);
    tcase_add_test(tc1_1, mn1);
    tcase_add_test(tc1_1, sub0);
    tcase_add_test(tc1_1, sub1);
    tcase_add_test(tc1_1, sum0);
    tcase_add_test(tc1_1, sum1);
    tcase_add_test(tc1_1, transp0);
    tcase_add_test(tc1_1, transp1);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
