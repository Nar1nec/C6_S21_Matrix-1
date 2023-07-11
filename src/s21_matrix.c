#include "s21_matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    int answer;
    if(size_compare(A,B)){
        answer = s21_create_matrix(A->rows,B->columns,result);
        for(int i = 0; i < result->rows; i++){
            for(int j = 0; j < result->columns; j++){
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
    }
    else{
        answer = ERROR_CALCULATION;
    }
    return answer;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    int answer;
    if(size_compare(A,B)){
        answer = s21_create_matrix(A->rows,B->columns,result);
        if(!answer){
            for(int i = 0; i < result->rows; i++){
                for(int j = 0; j < result->columns; j++){
                    result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
                }
            }
        }
    }
    else{
        answer = ERROR_CALCULATION;
    }
    return answer;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result){
    int answer = s21_create_matrix(A->rows,A->columns,result);;
    for(int i = 0; i < result->rows; i++){
        for(int j = 0; j < result->columns; j++){
            result->matrix[i][j] = A->matrix[i][j] * number;
        }
    }
    return answer;
}

int size_compare(matrix_t *A, matrix_t *B){
    return ((A->rows != B->rows) || (A->columns != B->columns)) ? SUCCESS : FAILURE;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    int answer;
    if(A->columns == B->rows){
        answer = s21_create_matrix(A->rows,B->columns,result);
        for(int i = 0; i < A->rows - 1; i++){
            for(int j = 0; j < B->columns; j++){
                for(int k = 0; k < A->columns; k++){
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
    }
    else{
        answer = ERROR_CALCULATION;
    }
    return answer;
}

int s21_transpose(matrix_t *A, matrix_t *result){
    int answer = s21_create_matrix(A->columns,A->rows,result);
    if(!answer){
        for(int i = 0; i < A->rows; i++){
            for(int j = 0; j < A->columns;j++){
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
    }
    return answer;
}

int s21_calc_complements(matrix_t *A, matrix_t *result){
    
}