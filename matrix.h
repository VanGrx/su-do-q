#ifndef MATRIX_H
#define MATRIX_H
#include <QString>
#include <iostream>
#include <vector>

class Matrix {
public:
  // Matrix(FILE *fRead);
  Matrix();
  void printMatrix();
  void createMatrixFromFile();
  void parseMatrixAsString();
  QString getStringMatrix();
  void updatePossibleMatrix(int num, int i, int j);
  void initializePossibleMatrix();
  void printPossibleMatrix();

private:
  int m_solution_matrix[9][9];
  std::vector<int> m_possible_matrix[9][9];
  QString m_string_matrix;
};

#endif // MATRIX_H
