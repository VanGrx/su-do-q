#include "sudoku.h"
#include "matrix.h"

Sudoku::Sudoku() {}

Sudoku::Sudoku(QString input_numbers) {
  Matrix m = Matrix(input_numbers);
  calculation.push_back(m);
}

QString Sudoku::resolve() {

  calculation.at(0).solveSingleElements();
  if (!calculation.at(0).isSolvable())
    return "not_solvable";

  if (calculation.at(0).getRemaining() != 0) {
    // in case only 2 posibilities are remaining:
    Matrix m1 = Matrix(calculation.at(0));

    int i = 0; // calculation.at(0).findMinPossibilityIndexes().getI();
    int j = 0; // calculation.at(0).findMinPossibilityIndexes().getJ();
    //    // premise: lowest number of possible elements is 2
    //    // starter matrix finds cell with min possible elements
    //    // inserts 1st element (i,j,0)
    //    //    calculation.at(0).setSolutionMatrix(
    //    //        i, j, calculation.at(0).getPossibleMatrixValue(i, j, 0));

    //    // new matrix inserts the second element (i,j,1)
    m1.setSolutionMatrix(i, j,
                         calculation.at(0).getPossibleMatrixValue(i, j, 1));
    m1.solveSingleElements();
    //    calculation.push_back(m1);
  }
  return (calculation.end() - 1)->getStringMatrix();
}
