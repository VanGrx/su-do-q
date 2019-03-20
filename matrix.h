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
  void parseMatrixAsString();
  QString getStringMatrix() const;
  void updatePossibleMatrix(int num, int i, int j);
  void initializePossibleMatrix();
  void solveSingleElements();
  void findMinPossibilities();
  void prepareMatrix();
  ~Matrix();
  void updateColumn(int num, int i, int j);
  void updateRow(int num, int i, int j);
  void updateBox(int num, int i, int j);
  void setSolutionMatrix(int i, int j, int num);
  unsigned getRemaining();
  bool isSolvable();
  enum status { UNSOLVED = 0, SOLVED, UNSOLVABLE };
  int getStatus() const;
  int min_x;
  int min_y;
  std::vector<int> min_poss;

private:
  unsigned int m_remaining_empty;
  int m_solution_matrix[9][9];
  std::vector<int> m_possible_matrix[9][9];
  QString m_string_matrix;
  int m_status = UNSOLVED;
};

#endif // MATRIX_H
