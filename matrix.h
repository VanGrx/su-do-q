#ifndef MATRIX_H
#define MATRIX_H
#include <QString>
#include <iostream>
#include <vector>

class singlePosibility {
public:
  singlePosibility(int i, int j);
  int getI() const;
  int getJ() const;

private:
  int m_i;
  int m_j;
};

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
  void solveSingleElements();
  void storeSinglePosibility(int i, int j);

private:
  int m_solution_matrix[9][9];
  std::vector<int> m_possible_matrix[9][9];
  QString m_string_matrix;
  std::vector<singlePosibility> m_store_possible;
};

#endif // MATRIX_H
