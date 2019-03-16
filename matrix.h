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
  Matrix();
  Matrix(QString input);
  void printMatrix() const;
  void createMatrixFromFile();
  void parseMatrixAsString();
  QString getStringMatrix() const;
  void updatePossibleMatrix(int num, int i, int j);
  void initializePossibleMatrix();
  void printPossibleMatrix() const;
  void solveSingleElements();
  void storeSinglePosibility(int i, int j);
  void prepareMatrix();
  ~Matrix();
  void updateColumn(int num, int i, int j);
  void updateRow(int num, int i, int j);
  void updateBox(int num, int i, int j);

private:
  int m_solution_matrix[9][9];
  std::vector<int> m_possible_matrix[9][9];
  QString m_string_matrix;
  std::vector<singlePosibility> m_store_possible;
};

#endif // MATRIX_H
