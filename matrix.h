#ifndef MATRIX_H
#define MATRIX_H
#include <QString>
#include <iostream>
#include <vector>

class singlePosibility {
public:
  singlePosibility();
  singlePosibility(int i, int j);
  int getI() const;
  int getJ() const;
  void setI(int i);
  void setJ(int j);

private:
  int m_i;
  int m_j;
};

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
  singlePosibility findMinPossibilityIndexes();
  int getPossibleMatrixValue(int i, int j, int pos);
  bool isSolvable();

private:
  unsigned int m_remaining_empty;
  int m_solution_matrix[9][9];
  std::vector<int> m_possible_matrix[9][9];
  QString m_string_matrix;
  std::vector<singlePosibility> m_store_possible;
};

#endif // MATRIX_H
