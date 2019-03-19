#include "sudoku.h"
#include "matrix.h"

Sudoku::Sudoku() {}

Sudoku::Sudoku(QString input_numbers) {
  Matrix *m = new Matrix(input_numbers);
  calculation.push_back(m);
}

QString Sudoku::resolve() {

  calculation.at(0)->solveSingleElements();

  // Initial Matrix is unsolvable. We exit with message.
  if (calculation.at(0)->getStatus() == Matrix::UNSOLVABLE)
    return "not_solvable";
  // Initial Matrix is solved. We return the solution.
  if (calculation.at(0)->getStatus() == Matrix::SOLVED)
    return calculation.back()->getStringMatrix();

  // Initial Matrix is not solved. We create a new with added values

  while (!calculation.empty()) {
    while (!calculation.back()->min_poss.empty()) {

      Matrix *m = new Matrix(*calculation.back());

      m->setSolutionMatrix(calculation.back()->min_x, calculation.back()->min_y,
                           calculation.back()->min_poss.back());

      calculation.back()->min_poss.pop_back();
      m->solveSingleElements();

      calculation.push_back(m);

      if (calculation.back()->getStatus() == Matrix::SOLVED)
        return calculation.back()->getStringMatrix();
      if (calculation.back()->getStatus() == Matrix::UNSOLVED) {
      } else
        calculation.pop_back();
    }

    calculation.pop_back();
  }

  return "not_solvable";
}
