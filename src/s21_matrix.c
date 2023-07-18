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

void find_minor(int excluded_r_с, matrix_t *result, matrix_t *minor) {
  s21_create_matrix(result->columns - 1, result->rows - 1, minor);
  int minor_i = 0;
  for (int i = 0; i < result->rows; i++) {
    if (i == excluded_r_с) continue;
    int minor_j = 0;
    for (int j = 0; j < result->columns; j++) {
      if (j == excluded_r_с) continue;
      minor->matrix[minor_i][minor_j] = result->matrix[i][j];
      minor_j++;
    }
    minor_i++;
  }
}

// int s21_calc_complements(matrix_t *A, matrix_t *result) {
//   if (A->rows == A->columns) {
//     int answer = s21_create_matrix(A->columns, A->rows, result);
//     if (!answer) {
//       if (A->columns == 1) {
//         result->matrix = A->matrix;
//       } else if (A->columns == 2) {
//         for (int i = 0; i < A->rows; i++) {
//           for (int j = 0; k < A->columns; j++) {
//             matrix_t minor_matrix;
//             find_minor(A->rows, result, &minor_matrix);
//             result->matrix[i][j] = minor_matrix.matrix[0][0] * pow(-1, i + j);
//             s21_remove_matrix(&minor_matrix);
//           }
//         }
//       } else if(A->columns >= 3){
//         for (int i = 0; i < A->rows; i++) {
//           for (int j = 0; k < A->columns; j++) {
//             matrix_t minor_matrix;
//             find_minor(A->rows, result, &minor_matrix);
//             result->matrix[i][j] = minor_matrix.matrix[0][0] * pow(-1, i + j);
//             s21_remove_matrix(&minor_matrix);
//           }
//         }
//       }
//     }
//   } else {
//     answer = ERROR_CALCULATION;
//   }
//   return answer;
// }

double calc_determinant(matrix_t* result){
  double det = 0.0;

  if (result->rows == 1) {
    det = result->matrix[0][0];
  } else if (result->rows == 2) {
    det = result->matrix[0][0] * result->matrix[1][1] - result->matrix[0][1] * result->matrix[1][0];
  } else if(result->rows >= 3){
    double sign = 1.0;
  for(int i = 0; i < result->columns; i++){
    for (int j = 0; j < result->columns; j++) {
      matrix_t minor_matrix;
      find_minor(j, result, &minor_matrix);
      det += sign * result->matrix[0][j] * calc_determinant(&minor_matrix) * pow(-1, i + j);
      sign = -sign;
      s21_remove_matrix(&minor_matrix);
    }
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

// int just_determinant(matrix_t *A) {
//   double summ = 0;
//   if (A->rows == 1) summ = A->matrix[0][0];
//   if (A->rows == 2) {
//     summ =
//         A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] *
//         A->matrix[1][0];
//   }
//   if (A->rows >= 3) {
//     fi(A->rows) {
//       fj(A->columns) {
//         matrix_t minor;
//         select_minor_matrix(A, &minor, i, j);
//         summ += A->matrix[i][j] * pow(-1, i + j) * just_determinant(&minor);
//         s21_remove_matrix(&minor);
//       }
//       return summ;
//     }
//   }
//   return summ;
// }