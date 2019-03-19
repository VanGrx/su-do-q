#ifndef MATRIX_H
#define MATRIX_H
#include <QString>
#include <iostream>
#include <vector>

class Matrix {
public:
  Matrix();
  Matrix(QString input);
  Matrix(const Matrix &other);
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
  void setSolutionMatrix(int i, int j, int num);
  unsigned getRemaining();
  int getPossibleMatrixValue(int i, int j, int pos);
  bool isSolvable();

private:
  unsigned int m_remaining_empty;
  int m_solution_matrix[9][9];
  std::vector<int> m_possible_matrix[9][9];
  QString m_string_matrix;
};

#endif // MATRIX_H
