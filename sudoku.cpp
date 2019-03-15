#include "sudoku.h"
#include "matrix.h"

Sudoku::Sudoku() {}

Sudoku::Sudoku(QString input_numbers) {}

QString Sudoku::resolve() {
  Matrix m;
  m.createMatrixFromFile();
  // Sudoku *starter = new Sudoku();
  // starter->calculation.push_back(m);
  m.solveSingleElements();

  return m.getStringMatrix();
}
