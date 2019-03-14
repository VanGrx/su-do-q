#include "sudoku.h"
#include "matrix.h"

Sudoku::Sudoku() {}

Sudoku::Sudoku(QString input_numbers) {}

QString Sudoku::resolve() {
  Matrix m;
  m.createMatrixFromFile();

  // Sudoku *starter = new Sudoku();
  return m.getStringMatrix();
}
