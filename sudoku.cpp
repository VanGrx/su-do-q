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

      // Create a new matrix
      Matrix *m = new Matrix(*calculation.back());

      // Set one possible solution
      m->setSolutionMatrix(calculation.back()->min_x, calculation.back()->min_y,
                           calculation.back()->min_poss.back());
      calculation.back()->min_poss.pop_back();
      // Try to solve the new matrix
      m->solveSingleElements();
      // Add it to the vector
      calculation.push_back(m);

      // If the last one is solved, we found the solution
      if (calculation.back()->getStatus() == Matrix::SOLVED)
        return calculation.back()->getStringMatrix();
      // if it is UNSOLVABLE. We remove the last matrix
      // and try another solution.
      if (calculation.back()->getStatus() == Matrix::UNSOLVABLE)
        calculation.pop_back();
      // if it is newither, then it is unsolved yet, we continue the same
      // process on the new matrix
    }
    calculation.pop_back();
  }

  return "not_solvable";
}
