#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void set_matrix(matrix_t *A, double in_matrix[][10]) {
  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++) A->matrix[i][j] = in_matrix[i][j];
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int answer = OK;

  if (rows <= 0 || columns <= 0) {
    answer = ERROR_INVALID_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;

    result->matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
    }
  }

  return answer;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int answer = SUCCESS;

  if ((A->rows == B->rows) && (A->columns == B->columns)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          answer = FAILURE;
          break;
        }
      }
      if (!answer) {
        break;
      }
    }
  } else {
    answer = FAILURE;
  }

  return answer;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int answer;
  if (size_compare(A, B)) {
    answer = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else {
    answer = ERROR_CALCULATION;
  }
  return answer;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int answer;
  if (size_compare(A, B)) {
    answer = s21_create_matrix(A->rows, B->columns, result);
    if (!answer) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  } else {
    answer = ERROR_CALCULATION;
  }
  return answer;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int answer = s21_create_matrix(A->rows, A->columns, result);
  if (!answer) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    answer = ERROR_CALCULATION;
  }
  return answer;
}

int size_compare(matrix_t *A, matrix_t *B) {
  return ((A->rows != B->rows) || (A->columns != B->columns)) ? SUCCESS
                                                              : FAILURE;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int answer;
  if (A->columns == B->rows) {
    answer = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows - 1; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  } else {
    answer = ERROR_CALCULATION;
  }
  return answer;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int answer = s21_create_matrix(A->columns, A->rows, result);
  if (!answer) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    answer = ERROR_CALCULATION;
  }
  return answer;
}

void find_minor(int excluded_c,int excluded_r, matrix_t *result, matrix_t *minor) {
  s21_create_matrix(result->columns - 1, result->rows - 1, minor);
  int minor_i = 0;
  for (int i = 0; i < result->rows; i++) {
    if (i == excluded_r) continue;
    int minor_j = 0;
    for (int j = 0; j < result->columns; j++) {
      if (j == excluded_c) continue;
      minor->matrix[minor_i][minor_j] = result->matrix[i][j];
      minor_j++;
    }
    minor_i++;
  }
}

double calc_determinant(matrix_t* result){
  double det = 0.0;

  if (result->rows == 1) {
    det = result->matrix[0][0];
  } else if (result->rows == 2) {
    det = result->matrix[0][0] * result->matrix[1][1] - result->matrix[0][1] * result->matrix[1][0];
  } else if(result->rows >= 3){
  for(int i = 0; i < result->rows; i++){
    for (int j = 0; j < result->columns; j++) {
      matrix_t minor_matrix;
      find_minor(i, j, result, &minor_matrix);
      det += result->matrix[i][j] * calc_determinant(&minor_matrix) * pow(-1, i + j);
      s21_remove_matrix(&minor_matrix);
    }
    return det;
  }
  }

  return det;
}

int s21_determinant(matrix_t *A, double *result){
  int answer = OK;
  if(A->rows == A->columns){
    *result = calc_determinant(A);
  }else{
    answer = ERROR_CALCULATION;
  }
  return answer;
}
