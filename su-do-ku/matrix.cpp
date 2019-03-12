#include "matrix.h"

Matrix::Matrix() {
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j)
      solution_matrix[i][j] = 0;
}
