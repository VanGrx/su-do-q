#include "sudoku.h"
#include "matrix.h"

Sudoku::Sudoku() {}

Sudoku::Sudoku(QString input_numbers) {
  Matrix m = Matrix(input_numbers);
  calculation.push_back(m);
}

QString Sudoku::resolve() {
  calculation.at(0).solveSingleElements();
  return calculation.at(0).getStringMatrix();
}
