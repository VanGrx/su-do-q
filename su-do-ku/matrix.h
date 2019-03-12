#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>

class Matrix {
public:
  Matrix();

private:
  int solution_matrix[9][9];
  std::vector<int> possible_matrix[9][9];
};

#endif // MATRIX_H
